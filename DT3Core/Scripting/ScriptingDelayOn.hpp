#pragma once
#ifndef DT3_SCRIPTINGDELAYON
#define DT3_SCRIPTINGDELAYON
//==============================================================================
///
///    File: ScriptingDelayOn.hpp
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
/// Delays a boolean transition from 0 to 1.
//==============================================================================

class ScriptingDelayOn: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingDelayOn,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingDelayOn        (void);
                                    ScriptingDelayOn        (const ScriptingDelayOn &rhs);
        ScriptingDelayOn &            operator =                (const ScriptingDelayOn &rhs);
        virtual                     ~ScriptingDelayOn        (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

        /// Object was added to a world
        /// world world that object was added to
        virtual void add_to_world(World *world) override;

        /// Object was removed from a world
        virtual void remove_from_world(void) override;

    public:
        /// Registered with world to tick this node
        /// \param dt delta time
        void                        tick                    (const DTfloat dt);

    private:
        DTfloat                        _time;
        DTfloat                        _delay;

        Plug<bool>                _in;
        Plug<bool>                _out;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
