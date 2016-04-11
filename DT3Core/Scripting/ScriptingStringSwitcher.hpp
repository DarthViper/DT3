#pragma once
#ifndef DT3_SCRIPTINGSTRINGSWITCHER
#define DT3_SCRIPTINGSTRINGSWITCHER
//==============================================================================
///
///    File: ScriptingStringSwitcher.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Scripting/ScriptingBase.hpp"
#include <string>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Switcher for strings.
//==============================================================================

class ScriptingStringSwitcher: public ScriptingBase {
    public:
        DEFINE_TYPE(ScriptingStringSwitcher,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                    ScriptingStringSwitcher                (void);
                                    ScriptingStringSwitcher                (const ScriptingStringSwitcher &rhs);
        ScriptingStringSwitcher &                operator =                (const ScriptingStringSwitcher &rhs);
        virtual                     ~ScriptingStringSwitcher            (void);

        virtual void                archive                 (const std::shared_ptr<Archive> &archive);

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool                    compute                    (const PlugBase *plug);

        DEFINE_ACCESSORS_REF(string1, set_string1, std::string, _in_string1);
        DEFINE_ACCESSORS_REF(string2, set_string2, std::string, _in_string2);
        DEFINE_ACCESSORS_REF(string3, set_string3, std::string, _in_string3);
        DEFINE_ACCESSORS_REF(string4, set_string4, std::string, _in_string4);
        DEFINE_ACCESSORS_REF(string5, set_string5, std::string, _in_string5);
        DEFINE_ACCESSORS_REF(string6, set_string6, std::string, _in_string6);
        DEFINE_ACCESSORS_REF(string7, set_string7, std::string, _in_string7);
        DEFINE_ACCESSORS_REF(string8, set_string8, std::string, _in_string8);
        DEFINE_ACCESSORS_REF(string9, set_string9, std::string, _in_string9);
        DEFINE_ACCESSORS_REF(string10, set_string10, std::string, _in_string10);
        DEFINE_ACCESSORS_REF(string11, set_string11, std::string, _in_string11);
        DEFINE_ACCESSORS_REF(string12, set_string12, std::string, _in_string12);
        DEFINE_ACCESSORS_REF(string13, set_string13, std::string, _in_string13);
        DEFINE_ACCESSORS_REF(string14, set_string14, std::string, _in_string14);
        DEFINE_ACCESSORS_REF(string15, set_string15, std::string, _in_string15);
        DEFINE_ACCESSORS_REF(string16, set_string16, std::string, _in_string16);

    private:
        Plug<bool>                _in1;
        Plug<std::string>            _in_string1;
        Plug<bool>                _in2;
        Plug<std::string>            _in_string2;
        Plug<bool>                _in3;
        Plug<std::string>            _in_string3;
        Plug<bool>                _in4;
        Plug<std::string>            _in_string4;
        Plug<bool>                _in5;
        Plug<std::string>            _in_string5;
        Plug<bool>                _in6;
        Plug<std::string>            _in_string6;
        Plug<bool>                _in7;
        Plug<std::string>            _in_string7;
        Plug<bool>                _in8;
        Plug<std::string>            _in_string8;
        Plug<bool>                _in9;
        Plug<std::string>            _in_string9;
        Plug<bool>                _in10;
        Plug<std::string>            _in_string10;
        Plug<bool>                _in11;
        Plug<std::string>            _in_string11;
        Plug<bool>                _in12;
        Plug<std::string>            _in_string12;
        Plug<bool>                _in13;
        Plug<std::string>            _in_string13;
        Plug<bool>                _in14;
        Plug<std::string>            _in_string14;
        Plug<bool>                _in15;
        Plug<std::string>            _in_string15;
        Plug<bool>                _in16;
        Plug<std::string>            _in_string16;

        bool                   _buffer_output;
        Plug<std::string>            _out;

};

//==============================================================================
//==============================================================================

} // DT3

#endif
