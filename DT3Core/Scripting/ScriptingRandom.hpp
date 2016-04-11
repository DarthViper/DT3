#pragma once
//==============================================================================
///
///    File: ScriptingRandom.hpp
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
/// Random numbers.
//==============================================================================

class ScriptingRandom: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingRandom,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingRandom            (void);
                                    ScriptingRandom            (const ScriptingRandom &rhs);
        ScriptingRandom &            operator =                (const ScriptingRandom &rhs);
        virtual                        ~ScriptingRandom        (void);

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

        /// Set Event
        void                        eventGenerate           (PlugNode *sender);

    private:
        Plug<DTfloat>                    _out;

        Plug<bool>                    _continuous;
        Event                           _generate_e;
};

//==============================================================================
//==============================================================================

} // DT3
