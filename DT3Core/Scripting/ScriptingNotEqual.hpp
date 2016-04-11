#pragma once
#ifndef DT3_SCRIPTINGNOTEQUAL
#define DT3_SCRIPTINGNOTEQUAL
//==============================================================================
///
///    File: ScriptingNotEqual.hpp
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
/// Test for Inequality.
//==============================================================================

class ScriptingNotEqual: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingNotEqual,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingNotEqual       (void);
                                    ScriptingNotEqual       (const ScriptingNotEqual &rhs);
        ScriptingNotEqual &            operator =                (const ScriptingNotEqual &rhs);
        virtual                        ~ScriptingNotEqual        (void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive) override;

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool                    compute                    (const PlugBase *plug) override;

    private:
        Plug<DTfloat>                _in1;
        Plug<DTfloat>                _in2;
        Plug<bool>                _out;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
