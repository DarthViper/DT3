#pragma once
#ifndef DT3_SCRIPTINGBOOLSWITCHER
#define DT3_SCRIPTINGBOOLSWITCHER
//==============================================================================
///
///	File: ScriptingBoolSwitcher.hpp
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
/// Switcher for boolean values.
//==============================================================================

class ScriptingBoolSwitcher: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingBoolSwitcher,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingBoolSwitcher	(void);
                                    ScriptingBoolSwitcher	(const ScriptingBoolSwitcher &rhs);
        ScriptingBoolSwitcher &		operator =				(const ScriptingBoolSwitcher &rhs);
        virtual                     ~ScriptingBoolSwitcher	(void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive);

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool					compute					(const PlugBase *plug);

    private:
        Plug<bool>				_in1;
        Plug<bool>				_in_bool1;
        Plug<bool>				_in2;
        Plug<bool>				_in_bool2;
        Plug<bool>				_in3;
        Plug<bool>				_in_bool3;
        Plug<bool>				_in4;
        Plug<bool>				_in_bool4;
        Plug<bool>				_in5;
        Plug<bool>				_in_bool5;
        Plug<bool>				_in6;
        Plug<bool>				_in_bool6;
        Plug<bool>				_in7;
        Plug<bool>				_in_bool7;
        Plug<bool>				_in8;
        Plug<bool>				_in_bool8;

        Plug<bool>				_out;
        bool                   _buffer_output;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
