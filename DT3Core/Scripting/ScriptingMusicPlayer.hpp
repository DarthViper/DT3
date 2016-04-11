#pragma once
//==============================================================================
///
///    File: ScriptingMusicPlayer.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"
#include "DT3Core/Types/FileBuffer/FilePath.hpp"
#include "DT3Core/Types/Node/Event.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Controls Music playback.
//==============================================================================

class ScriptingMusicPlayer: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingMusicPlayer,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingMusicPlayer    (void);
                                    ScriptingMusicPlayer    (const ScriptingMusicPlayer &rhs);
        ScriptingMusicPlayer &        operator =                (const ScriptingMusicPlayer &rhs);
        virtual                     ~ScriptingMusicPlayer    (void);

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

        /// Play Event
        void                        play                    (PlugNode *sender);

        /// Stop Event
        void                        stop                    (PlugNode *sender);

    private:
        Event                       _play;
        Event                       _stop;

        Plug<FilePath>                _path;
        Plug<DTfloat>                _gain;

        Plug<bool>                _is_playing;
        Plug<bool>                _stop_on_destroy;

        Plug<bool>                _loop;
};

//==============================================================================
//==============================================================================

} // DT3
