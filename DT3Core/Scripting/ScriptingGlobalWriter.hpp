#pragma once
//==============================================================================
///
///    File: ScriptingGlobalWriter.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"
#include "DT3Core/Types/Node/Event.hpp"
#include <string>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Used to write a global value.
//==============================================================================

class ScriptingGlobalWriter: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingGlobalWriter,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingGlobalWriter    (void);
                                    ScriptingGlobalWriter    (const ScriptingGlobalWriter &rhs);
        ScriptingGlobalWriter &        operator =                (const ScriptingGlobalWriter &rhs);
        virtual                     ~ScriptingGlobalWriter    (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

    public:
        /// Write Event
        void                        write                   (PlugNode *sender);

    private:
        Plug<std::string>            _global;
        Plug<std::string>            _value;

        Plug<bool>                _persistent;

        Event                       _write_e;
};

//==============================================================================
//==============================================================================

} // DT3
