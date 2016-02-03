#pragma once
#ifndef DT3_SCRIPTINGAND
#define DT3_SCRIPTINGAND
//==============================================================================
///
///	File: ScriptingAND.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Logical AND.
//==============================================================================

class ScriptingAND: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingAND,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingAND			(void);
                                    ScriptingAND			(const ScriptingAND &rhs);
        ScriptingAND &				operator =				(const ScriptingAND &rhs);
        virtual                     ~ScriptingAND			(void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive);

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool					compute					(const PlugBase *plug);

    private:
        Plug<bool>				_in1;
        Plug<bool>				_in2;
        Plug<bool>				_in3;
        Plug<bool>				_in4;
        Plug<bool>				_in5;
        Plug<bool>				_in6;
        Plug<bool>				_in7;
        Plug<bool>				_in8;

        Plug<bool>				_out;
        Plug<bool>				_out_inv;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
