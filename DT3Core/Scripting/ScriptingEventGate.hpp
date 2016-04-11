#pragma once
//==============================================================================
///
///    File: ScriptingEventGate.hpp
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
/// Class
//==============================================================================

class ScriptingEventGate: public ScriptingBase {
        /// Flip-Flop.

    public:
        DEFINE_TYPE(ScriptingEventGate,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingEventGate        (void);
                                    ScriptingEventGate        (const ScriptingEventGate &rhs);
        ScriptingEventGate &        operator =                (const ScriptingEventGate &rhs);
        virtual                     ~ScriptingEventGate        (void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive) override;

    public:
        /// Toggle Event
        void                        event_in                (PlugNode *sender);

    private:
        Plug<bool>                _enable;

        Event                       _event_in;
        Event                       _event_out;
};

//==============================================================================
//==============================================================================

} // DT3
