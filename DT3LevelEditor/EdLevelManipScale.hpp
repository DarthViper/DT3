#pragma once
//==============================================================================
///
///    File: EdLevelManipScale.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelTool.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

namespace DT3 {
    class PlaceableObject;
    class CameraObject;
    class Matrix4;
    class MaterialResource;
    class ShaderResource;
}

class EdLevelToolWindow;
class EdLevelToolEvent;

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
/// Class
//==============================================================================

class EdLevelManipScale: public EdLevelTool
{
    Q_OBJECT
    Q_CLASSINFO("tool_name","Scale")

    public:

                        EdLevelManipScale       (QObject *parent=nullptr);
        virtual         ~EdLevelManipScale      (void)  {}

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

        std::shared_ptr<DT3::MaterialResource>   _tool_material;
        std::shared_ptr<DT3::ShaderResource>     _shader;

        unsigned int                              _starting_axis;
        int                               _mouse_x;
        int                               _mouse_y;
};

//==============================================================================
//==============================================================================

