#pragma once
#ifndef DT3_CONTEXTSWITCHER
#define DT3_CONTEXTSWITCHER
//==============================================================================
///
///    File: ContextSwitcher.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================
///
/// Based heavily on the cross platform Context routines from libtask
/// Portions copyright Copyright (c) 2005-2006 Russ Cox, MIT
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"

namespace DT3 {

//==============================================================================
//==============================================================================

struct mcontext {

#if DT3_CPU == DT3_INTEL && DT3_POINTER_SIZE == DT3_32_BIT
    uint32_t      gregs[65];
#elif DT3_CPU == DT3_INTEL && DT3_POINTER_SIZE == DT3_64_BIT
    uint64_t    gregs[100]; // 8 bytes each on AMD64
#elif DT3_CPU == DT3_ARM
    uint32_t      gregs[16];
    DTdouble    fregs[32];
#endif

};

//==============================================================================
//==============================================================================

struct uContext {
    mcontext            uc_mcontext;
    uint32_t              uc_stack_ss;
    uint8_t*            uc_stack_sp;
};

//==============================================================================
//==============================================================================

class ContextSwitcher {

    private:

                            ContextSwitcher     (void);
                            ContextSwitcher     (const ContextSwitcher &rhs);
        ContextSwitcher&    operator =          (const ContextSwitcher &rhs);
                            ~ContextSwitcher    (void);

    public:

        static int32_t        swap_context        (uContext *oucp, const uContext *ucp);
        static void         make_context        (uContext *ucp, void (*func)(void*), void *data);

        static int32_t        context             (uContext*ucp);
        static void         set_context         (const uContext*ucp);

};
//==============================================================================
//==============================================================================

} // DT3

#endif
