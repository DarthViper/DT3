#pragma once
//==============================================================================
///
///    File: Debug.hpp
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
//==============================================================================
inline void dt3_debug_break() {
#ifdef DT3_DEBUG
    #if DT3_CPU == DT3_INTEL
        #if DT3_COMPILER == DT3_GCC
            asm volatile ("int3;");
        #elif DT3_COMPILER == DT3_VISUALC
            asm { int 3 };
        #else
        #endif    // DT3_COMPILER
    #endif
#endif    // DT3_DEBUG
}

//==============================================================================
//==============================================================================

} // DT3
