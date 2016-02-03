#pragma once
//==============================================================================
///
///	File: ScriptingPulseNoReset.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"
#include "DT3Core/Types/Node/Event.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Outputs a pulse.
//==============================================================================

class ScriptingPulseNoReset: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingPulseNoReset,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingPulseNoReset	(void);
                                    ScriptingPulseNoReset	(const ScriptingPulseNoReset &rhs);
        ScriptingPulseNoReset &		operator =				(const ScriptingPulseNoReset &rhs);
        virtual                     ~ScriptingPulseNoReset	(void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive);

        /// Object was added to a world
        /// world world that object was added to
        virtual void                add_to_world            (World *world);

        /// Object was removed from a world
        virtual void                remove_from_world       (void);

    public:
        /// Registered with world to tick this node
        /// \param dt delta time
        void                        tick                    (const DTfloat dt);

        /// Event
        void                        eventIn                 (PlugNode *sender);

    private:
        DTfloat						_time;
        DTfloat						_pulse_time;

        bool                   _event_in;

        Plug<bool>				_in;
        Plug<bool>				_out;

        Event                       _in_e;
};

//==============================================================================
//==============================================================================

} // DT3
