#pragma once
#ifndef DT3_SCRIPTINGTIMER
#define DT3_SCRIPTINGTIMER
//==============================================================================
///
///    File: ScriptingTimer.hpp
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
/// Standard timer
//==============================================================================

class ScriptingTimer: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingTimer,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingTimer            (void);
                                    ScriptingTimer            (const ScriptingTimer &rhs);
        ScriptingTimer &            operator =              (const ScriptingTimer &rhs);
        virtual                     ~ScriptingTimer         (void);

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
        Plug<DTfloat>                _speed;
        Plug<bool>                _count_up;
        Plug<bool>                _count_down;
        Plug<DTfloat>                _time;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
