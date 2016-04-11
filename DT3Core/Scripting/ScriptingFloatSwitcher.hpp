#pragma once
#ifndef DT3_SCRIPTINGFLOATSWITCHER
#define DT3_SCRIPTINGFLOATSWITCHER
//==============================================================================
///
///    File: ScriptingFloatSwitcher.hpp
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
/// Switcher for float values.
//==============================================================================

class ScriptingFloatSwitcher: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingFloatSwitcher,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingFloatSwitcher    (void);
                                    ScriptingFloatSwitcher    (const ScriptingFloatSwitcher &rhs);
        ScriptingFloatSwitcher &    operator =                (const ScriptingFloatSwitcher &rhs);
        virtual                     ~ScriptingFloatSwitcher    (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

    public:

        /// Computes the value of the node
        /// \param plug plug to compute
        bool compute(const PlugBase *plug) override;

        DEFINE_ACCESSORS(float1, set_float1, DTfloat, _in_float1);
        DEFINE_ACCESSORS(float2, set_float2, DTfloat, _in_float2);
        DEFINE_ACCESSORS(float3, set_float3, DTfloat, _in_float3);
        DEFINE_ACCESSORS(float4, set_float4, DTfloat, _in_float4);

    private:
        Plug<bool>                _in1;
        Plug<DTfloat>                _in_float1;
        Plug<bool>                _in2;
        Plug<DTfloat>                _in_float2;
        Plug<bool>                _in3;
        Plug<DTfloat>                _in_float3;
        Plug<bool>                _in4;
        Plug<DTfloat>                _in_float4;

        Plug<DTfloat>                _out;
        bool                   _buffer_output;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
