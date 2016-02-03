#pragma once
#ifndef DT3_SCRIPTINGSEQUENCER
#define DT3_SCRIPTINGSEQUENCER
//==============================================================================
///
///	File: ScriptingSequencer.hpp
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
/// Boolean sequencer.
//==============================================================================

class ScriptingSequencer: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingSequencer,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingSequencer		(void);
                                    ScriptingSequencer		(const ScriptingSequencer &rhs);
        ScriptingSequencer &		operator =				(const ScriptingSequencer &rhs);
        virtual                     ~ScriptingSequencer		(void);

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

    private:
        Plug<bool>				_go;
        Plug<bool>				_repeat;

        Plug<bool>				_out1;
        Plug<bool>				_out2;
        Plug<bool>				_out3;
        Plug<bool>				_out4;
        Plug<bool>				_out5;
        Plug<bool>				_out6;
        Plug<bool>				_out7;
        Plug<bool>				_out8;

        Plug<DTfloat>				_out_time1;
        Plug<DTfloat>				_out_time2;
        Plug<DTfloat>				_out_time3;
        Plug<DTfloat>				_out_time4;
        Plug<DTfloat>				_out_time5;
        Plug<DTfloat>				_out_time6;
        Plug<DTfloat>				_out_time7;
        Plug<DTfloat>				_out_time8;

        DTfloat						_time;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
