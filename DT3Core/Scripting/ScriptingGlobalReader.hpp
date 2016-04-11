#pragma once
//==============================================================================
///
///    File: ScriptingGlobalReader.hpp
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
/// Used to read a global value.
//==============================================================================

class ScriptingGlobalReader: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingGlobalReader,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingGlobalReader    (void);
                                    ScriptingGlobalReader    (const ScriptingGlobalReader &rhs);
        ScriptingGlobalReader &        operator =                (const ScriptingGlobalReader &rhs);
        virtual                     ~ScriptingGlobalReader    (void);

        virtual void archive(const std::shared_ptr<Archive> &archive) override;

    public:
        /// Read Event
        void                        read                    (PlugNode *sender);

    private:
        Plug<std::string>            _global;
        Plug<std::string>           _value;

        Event                       _read_e;
};

//==============================================================================
//==============================================================================

} // DT3
