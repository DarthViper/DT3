#pragma once
#ifndef DT3_SPHERICALHARMONICS
#define DT3_SPHERICALHARMONICS
//==============================================================================
///
///	File: SphericalHarmonics.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Math/Vector3.hpp"
#include <vector>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Class
//==============================================================================

class SphericalHarmonics {
    public:
        DEFINE_TYPE_SIMPLE_BASE(SphericalHarmonics)

        typedef DTfloat (*Polar_Function)(DTfloat theta, DTfloat phi);


                                                SphericalHarmonics		(void);
    private:
                                                SphericalHarmonics		(const SphericalHarmonics &rhs);
        SphericalHarmonics &					operator =              (const SphericalHarmonics &rhs);
    public:
                                                ~SphericalHarmonics		(void);

    public:
        /// Step 1. Build the list of samples that will be used to sample the environment
        /// \param num_bands Number of bands in the SH function
        /// \param num_samples Number of samples used to approximate the function
        void									build_spherical_samples	(int32_t num_bands, int32_t num_samples);

        /// Step 2. Sample the function and build the coefficients
        /// \param fn The function used to build the coefficients
        void									build_coefficients		(Polar_Function fn);

        /// Clear the samples
        void									clear_spherical_samples	(void);

        /// Return the number of bands in the function
        /// \return Number of bands
        int32_t									num_bands				(void)	{	return _num_bands;				}

        /// Return the number of coefficients in the function
        /// \return Number of coefficients
        int32_t									num_coefficients		(void)	{	return _num_bands*_num_bands;	}

        /// Returns the coefficients
        /// \return coefficients
        const std::vector<DTfloat> &            coefficients            (void)	{	return _coeff;					}

        /// Clear all of the calculated coefficients
        void									clear_coefficients		(void);

    private:

        DTfloat									legendre				(int32_t l,int32_t m,DTfloat x);
        DTfloat									legendre_scale			(int32_t l, int32_t m);
        DTfloat									sH						(int32_t l, int32_t m, DTfloat theta, DTfloat phi);

        int32_t									_num_bands;
        int32_t									_num_samples;
        int32_t									_num_samples_sqrt;

        struct SHSample {
            Vector3                 _sph;
            Vector3                 _vec;
            std::vector<DTfloat>    _coeff;     // numCoefficients large
        };

        std::vector<SHSample>					_samples;
        std::vector<DTfloat>					_coeff;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
