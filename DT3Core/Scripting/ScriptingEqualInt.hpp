#pragma once
#ifndef DT3_SCRIPTINGEQUALINT
#define DT3_SCRIPTINGEQUALINT
//==============================================================================
///
///    File: ScriptingEqualInt.hpp
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
/// Tests two ints for equality.
//==============================================================================

class ScriptingEqualInt: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingEqualInt,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingEqualInt        (void);
                                    ScriptingEqualInt        (const ScriptingEqualInt &rhs);
        ScriptingEqualInt &            operator =                (const ScriptingEqualInt &rhs);
        virtual                        ~ScriptingEqualInt        (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool compute(const PlugBase *plug) override;

    private:
        Plug<int32_t>                    _in1;
        Plug<int32_t>                    _in2;
        Plug<bool>                _out;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
