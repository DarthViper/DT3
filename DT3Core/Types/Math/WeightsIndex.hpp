#pragma once
#ifndef DT3_WEIGHTSINDEX
#define DT3_WEIGHTSINDEX
//==============================================================================
///
///    File: WeightsIndex.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class Stream;

//==============================================================================
/// Class
//==============================================================================

class WeightsIndex {
    public:
        DEFINE_TYPE_SIMPLE_BASE(WeightsIndex)

                                WeightsIndex        (void);
                                WeightsIndex        (const uint32_t w0, const uint32_t w1, const uint32_t w2, const uint32_t w3)  {    w[0] = w0; w[1] = w1; w[2] = w2; w[3] = w3;        }
                                WeightsIndex        (const WeightsIndex &rhs);
        WeightsIndex &            operator =            (const WeightsIndex &rhs);
                                ~WeightsIndex        (void)  {}

    public:

        bool               operator ==            (const WeightsIndex& rhs) const   {    return w[0] == rhs.w[0] && w[1] == rhs.w[1] && w[2] == rhs.w[2] && w[3] == rhs.w[3];    }
        bool               operator !=            (const WeightsIndex& rhs) const   {    return w[0] != rhs.w[0] || w[1] != rhs.w[1] || w[2] != rhs.w[2] || w[3] != rhs.w[3];    }

    public:
        uint32_t                 w[4];
};

//==============================================================================
/// Streaming operators
//==============================================================================

Stream& operator <<(Stream &s, const WeightsIndex&t);
Stream& operator >>(Stream &s, WeightsIndex&t);

//==============================================================================
//==============================================================================

} // DT3

#endif

