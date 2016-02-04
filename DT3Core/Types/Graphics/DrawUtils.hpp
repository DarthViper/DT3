#pragma once
//==============================================================================
///
///	File: DrawUtils.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include <string>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class Color4f;
class Color4b;
class Matrix4;
class Vector2;
class DrawBatcher;

class CameraObject;
class MaterialResource;
class ShaderResource;

//==============================================================================
/// Class
//==============================================================================

class DrawUtils {
    private:
                                        DrawUtils					(void);
                                        DrawUtils					(const DrawUtils &rhs);
        DrawUtils &						operator =					(const DrawUtils &rhs);
        virtual							~DrawUtils					(void);

    public:
        // Helper Drawing routines

        static void						draw_quad_stretch_center_3x3(   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Color4f &color,
                                                                        const Matrix4 &transform,
                                                                        DTfloat xpos,
                                                                        DTfloat ypos,
                                                                        DTfloat xsize,
                                                                        DTfloat ysize,
                                                                        DTfloat corner_width,
                                                                        DTfloat corner_height);

        static void						draw_quad_stretch_center_2x2(   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Color4f &color,
                                                                        const Matrix4 &transform,
                                                                        DTfloat xpos,
                                                                        DTfloat ypos,
                                                                        DTfloat xsize,
                                                                        DTfloat ysize,
                                                                        DTfloat corner_width,
                                                                        DTfloat corner_height);

        static void						draw_selection              (   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Matrix4 &transform,
                                                                        const Color4b &color,
                                                                        DTfloat radius);

        static void                     draw_cube                   (   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Matrix4 &transform,
                                                                        const Color4b &color,
                                                                        DTfloat size);
        static void                     draw_cube                   (   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Matrix4 &transform,
                                                                        DTfloat size);

        static void                     draw_cone                   (   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Matrix4 &transform,
                                                                        const Color4b &color,
                                                                        DTfloat radius,
                                                                        DTfloat length);
        static void                     draw_ring                   (   DrawBatcher &draw_batcher,
                                                                        const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Matrix4 &transform,
                                                                        const Color4b &color,
                                                                        DTfloat size);

        static void                     draw_bit_font               (   const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Vector2 &translation,
                                                                        const std::string &text);

        static void                     activate_state              (   const std::shared_ptr<CameraObject> &camera,
                                                                        const std::shared_ptr<MaterialResource> &material,
                                                                        const std::shared_ptr<ShaderResource> &shader,
                                                                        const Matrix4 &transform);

};

//==============================================================================
//==============================================================================

} // DT3
