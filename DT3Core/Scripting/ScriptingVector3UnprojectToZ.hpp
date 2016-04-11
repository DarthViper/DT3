#pragma once
#ifndef DT3_SCRIPTINGVECTOR3UNPROJECTTOZ
#define DT3_SCRIPTINGVECTOR3UNPROJECTTOZ
//==============================================================================
///
///    File: ScriptingVector3UnprojectToZ.hpp
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

class WorldNode;

//==============================================================================
/// Class
//==============================================================================

class ScriptingVector3UnprojectToZ: public ScriptingBase {
        /// Base object for the different placeable types of objects in the engine.

    public:
        DEFINE_TYPE(ScriptingVector3UnprojectToZ,ScriptingBase)
        DEFINE_CREATE_AND_CLONE
        DEFINE_PLUG_NODE

                                            ScriptingVector3UnprojectToZ    (void);
                                            ScriptingVector3UnprojectToZ    (const ScriptingVector3UnprojectToZ &rhs);
        ScriptingVector3UnprojectToZ &      operator =                      (const ScriptingVector3UnprojectToZ &rhs);
        virtual                             ~ScriptingVector3UnprojectToZ   (void);

        virtual void                        archive                 (const std::shared_ptr<Archive> &archive) override;

    public:
        /// Computes the value of the node
        /// \param plug plug to compute
        bool                           compute                      (const PlugBase *plug) override;

    private:
        Plug<Vector3>                       _in;
        Plug<std::shared_ptr<WorldNode>>    _camera;
        Plug<Vector3>                       _out;
        DTfloat                             _z;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
