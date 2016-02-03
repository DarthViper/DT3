//==============================================================================
///
///	File: ContextSwitcher.cpp
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
#include "DT3Core/Types/Utility/ContextSwitcher.hpp"
#include "DT3Core/Types/Utility/Assert.hpp"
#include <cstdarg>
#include <cstring>

//==============================================================================
//==============================================================================

extern "C" {
    extern	int     m_context(DT3::mcontext*);
    extern	void    set_m_context(const DT3::mcontext*);
}

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

int32_t ContextSwitcher::swap_context (uContext *oucp, const uContext *ucp)
{
    if(context(oucp) == 0)
        set_context(ucp);
    return 0;
}

void ContextSwitcher::make_context(uContext *ucp, void (*func)(void*), void *data)
{
#if DT3_CPU == DT3_INTEL && DT3_POINTER_SIZE == DT3_32_BIT
    ::memset(&ucp->uc_mcontext, 0, sizeof(ucp->uc_mcontext));

    uint32_t *sp = (uint32_t*)ucp->uc_stack_sp + ucp->uc_stack_ss/sizeof(void*);
    sp -= 1;
    sp = (uint32_t*)((uint32_t)sp - (uint32_t)sp%16);	/* 16-align for OS X */

    *sp = (uint64_t) data;
    ucp->uc_mcontext.gregs[1] = *sp;

    *--sp = 0;		// return address
    ucp->uc_mcontext.gregs[15] = (uint32_t)func;    // eip
    ucp->uc_mcontext.gregs[18] = (uint32_t)sp;      // esp

#elif DT3_CPU == DT3_INTEL && DT3_POINTER_SIZE == DT3_64_BIT
    ::memset(&ucp->uc_mcontext, 0, sizeof(ucp->uc_mcontext));

    uint64_t *sp = (uint64_t*)ucp->uc_stack_sp+ucp->uc_stack_ss/sizeof(void*);
    sp -= 1;
    sp = (uint64_t*)((uint64_t)sp - (uint64_t)sp%16);	/* 16-align for OS X */

    *sp = (uint64_t) data;
    ucp->uc_mcontext.gregs[1] = *sp;

    *--sp = 0;	// return address
    ucp->uc_mcontext.gregs[20] = (uint64_t)func;
    ucp->uc_mcontext.gregs[23] = (uint64_t)sp;

#elif DT3_CPU == DT3_ARM
    uint32_t *sp;

    sp = (uint32_t*)ucp->uc_stack_sp+ucp->uc_stack_ss/sizeof(void*);
    ucp->uc_mcontext.gregs[0] = (uint32_t) data;

    ucp->uc_mcontext.gregs[13] = (uint32_t)sp;
    ucp->uc_mcontext.gregs[14] = (uint32_t)func;

#else
    //#error Not available on this architecture yet!!
    ASSERT(false)
#endif

}

int32_t ContextSwitcher::context(uContext*ucp)
{
    return m_context( &(ucp->uc_mcontext) );
}

void ContextSwitcher::set_context(const uContext*ucp)
{
    set_m_context( &(ucp->uc_mcontext) );
}

//==============================================================================
//==============================================================================

} // DT3

