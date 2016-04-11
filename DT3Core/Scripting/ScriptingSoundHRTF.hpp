#pragma once
#ifndef DT3_SCRIPTINGSOUNDHRTF
#define DT3_SCRIPTINGSOUNDHRTF
//==============================================================================
///
///    File: ScriptingSoundHRTF.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingSoundBase.hpp"
#include "DT3Core/Types/Sound/SoundPacket.hpp"
#include "DT3Core/Types/Math/Matrix4.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class SoundResource;

//==============================================================================
//==============================================================================

const int16_t HRTF_LENGTH = 128;

struct HRTFFilterCoeffs {
    int32_t   num_angles;
    int32_t   max_angle;
    int16_t coeffs[37][2][HRTF_LENGTH];
};

//==============================================================================
/// Audio HRTF implementation.
//==============================================================================

class ScriptingSoundHRTF: public ScriptingSoundBase {
    public:
        DEFINE_TYPE(ScriptingSoundHRTF,ScriptingSoundBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingSoundHRTF        (void);
                                    ScriptingSoundHRTF        (const ScriptingSoundHRTF &rhs);
        ScriptingSoundHRTF &        operator =                (const ScriptingSoundHRTF &rhs);
        virtual                     ~ScriptingSoundHRTF      (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool compute(const PlugBase *plug) override;

    private:

        void                        calc_elev               (DTfloat elev, DTfloat &mix, const HRTFFilterCoeffs **e0, const HRTFFilterCoeffs **e1);
        void                        calc_azimuth            (DTfloat azimuth, const HRTFFilterCoeffs *e, DTfloat &mix, const int16_t **l0, const int16_t **r0, const int16_t **l1, const int16_t **r1);

        Plug<SoundPacket>                           _sound_packet_in;
        Plug<SoundPacket>                           _sound_packet_out;

        Plug<Vector3>                               _source_position;
        Plug<Matrix4>                               _listener_transform;

        int16_t                                     _buffer[HRTF_LENGTH];
        uint32_t                                      _buffer_index;

        DTfloat                                     _rolloff;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
