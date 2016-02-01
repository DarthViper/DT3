#pragma once
#ifndef EDLEVELMANIPPAN
#define EDLEVELMANIPPAN
//==============================================================================
///
///	File: EdLevelManipPan.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelTool.hpp"

// Qt include

// Engine includes
#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
#include "DT3Core/Resources/ResourceTypes/ShaderResource.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

namespace DT3 {
    class PlaceableObject;
    class CameraObject;
    class Matrix4;
}

class EdLevelToolWindow;
class EdLevelToolEvent;

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
/// Class
//==============================================================================

class EdLevelManipPan: public EdLevelTool
{
    public:
        DEFINE_TYPE(EdLevelManipPan, EdLevelTool)
        DEFINE_CREATE

                        EdLevelManipPan	(void);
        virtual         ~EdLevelManipPan(void)  {}

    public:
        virtual void    draw                    (const std::shared_ptr<CameraObject> &camera, float scale);

        virtual void    doEvent                 (const EdLevelToolEvent &event);

        virtual Matrix4 getManipulatorTransform (void) const;


    private:
        enum {
            PLUS_X = 1,
            PLUS_Y = 2,
            PLUS_Z = 3,
            CENTER = 4
        };

        std::shared_ptr<MaterialResource>   _tool_material;
        std::shared_ptr<ShaderResource>     _shader;



        // Tracking information
        float                           _starting_location_t1;
        float                           _starting_location_t2;
        unsigned int                              _starting_axis;

};

//==============================================================================
//==============================================================================

#endif
