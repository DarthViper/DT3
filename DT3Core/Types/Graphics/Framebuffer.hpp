#pragma once
//==============================================================================
///
///	File: Framebuffer.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseClass.hpp"
#include "DT3Core/Devices/DeviceGraphics.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Class
//==============================================================================

class Framebuffer: public BaseClass {
    public:
        DEFINE_TYPE_BASE(Framebuffer)
        DEFINE_CREATE

                                                    Framebuffer                 (void);
    private:
                                                    Framebuffer                 (const Framebuffer &rhs);
        Framebuffer &                               operator =                  (const Framebuffer &rhs);
    public:
        virtual                                     ~Framebuffer                (void);

    public:

        /// Allocate a framebuffer with color and depth texture
        /// \param width width of framebuffer
        /// \param height height of framebuffer
        /// \param color_format Format of color buffer
        /// \param depth_format Format of depth buffer
        void                                        allocate                    (int32_t width, int32_t height, DT3GLTextelFormat color_format, DT3GLTextelFormat depth_format, uint32_t num_color_targets = 1);

        /// Allocate a framebuffer with color and depth render buffer
        /// \param width width of framebuffer
        /// \param height height of framebuffer
        /// \param color_format Format of color buffer
        /// \param depth_format Format of depth buffer
        void                                        allocate                    (int32_t width, int32_t height, DT3GLTextelFormat color_format, DT3GLRenderBufferFormat depth_format, uint32_t num_color_targets = 1);

        /// Allocate a framebuffer with color render buffer and depth texture
        /// \param width width of framebuffer
        /// \param height height of framebuffer
        /// \param color_format Format of color buffer
        /// \param depth_format Format of depth buffer
        void                                        allocate                    (int32_t width, int32_t height, DT3GLRenderBufferFormat color_format, DT3GLTextelFormat depth_format);

        /// Returns the color texture if there is one
        /// \return color texture
        std::shared_ptr<DT3GLTexture2DResource>&    color_texture               (uint32_t color_target_index = 0);

        /// Returns the depth texture if there is one
        /// \return depth texture
        std::shared_ptr<DT3GLTexture2DResource>&    depth_texture               (void);

        /// Returns the color render buffer format
        /// \return Format
        DT3GLRenderBufferFormat                     color_renderbuffer_format   (void) const    {   return _rb_color_format;    }

        /// Returns the depth render buffer format
        /// \return Format
        DT3GLRenderBufferFormat                     depth_renderbuffer_format   (void) const    {   return _rb_depth_format;    }


        /// Returns width of framebuffer
        /// \return width
        int32_t                                       width                       (void) const    {   return _width;  }

        /// Returns height of framebuffer
        /// \return height
        int32_t                                       height                      (void) const    {   return _height;  }

        /// Activate the framebuffer
        void                                        activate                    (void);

    private:
        DT3GLRenderBufferFormat                                 _rb_color_format;
        DT3GLRenderBufferFormat                                 _rb_depth_format;
        int32_t                                                   _width;
        int32_t                                                   _height;

        std::vector<std::shared_ptr<DT3GLTexture2DResource>>    _color_texture;
        std::shared_ptr<DT3GLTexture2DResource>                 _depth_texture;

        std::shared_ptr<DT3GLFramebufferResource>               _framebuffer;

};

//==============================================================================
//==============================================================================

} // DT3
