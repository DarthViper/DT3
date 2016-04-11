#pragma once
//==============================================================================
///
///    File: ScriptingCounter.hpp
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
/// Event counter.
//==============================================================================

class ScriptingCounter: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingCounter,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingCounter        (void);
                                    ScriptingCounter        (const ScriptingCounter &rhs);
        ScriptingCounter &            operator =                (const ScriptingCounter &rhs);
        virtual                     ~ScriptingCounter        (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool compute(const PlugBase *plug) override;

        /// Set Event
        void                        event_incr              (PlugNode *sender);

        /// Reset Event
        void                        event_decr              (PlugNode *sender);

        /// Toggle Event
        void                        event_reset             (PlugNode *sender);

    private:
        Plug<int32_t>                 _min;
        Plug<int32_t>                 _max;
        Plug<bool>                _wrap;

        Event                       _incr_e;
        Event                       _decr_e;
        Event                       _reset_e;

        Plug<int32_t>                 _out;
};

//==============================================================================
//==============================================================================

} // DT3
