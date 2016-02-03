#pragma once
#ifndef DT3_DT3OPENGL
#define DT3_DT3OPENGL
//==============================================================================
///
///	File: DT3OpenGL.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Devices/DeviceGraphics.hpp"
#include "DT3OpenGL/DT3OpenGLResources.hpp"
#include <memory>
#include <cstring>
#include <list>
#include <map>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class LatentCall;
class Color4f;

//==============================================================================
/// Class
//==============================================================================

class DT3OpenGL: public DeviceGraphics {
        /// Multithreaded renderer implementation.

    public:
        DEFINE_TYPE(DT3OpenGL,DeviceGraphics)
        DEFINE_CREATE

                                DT3OpenGL                       (void);
                                DT3OpenGL                       (const DT3OpenGL&);
        DT3OpenGL &             operator =                      (const DT3OpenGL&);
                                ~DT3OpenGL                      (void);

    public:

        /// Screen context is ready
        virtual void                                        init_display                    (void);

        /// Opens up a display or tells the Device that a new display was opened
        /// \param width width of the display
        /// \param height width of the display
        virtual void                                        open_display                    (int32_t width, int32_t height);

        /// Changes a display or tells the Device that a display was changed
        /// \param width width of the display
        /// \param height width of the display
        virtual void                                        change_display                  (uint32_t width, uint32_t height);

        /// Closes a display or tells the Device that a display was closed
        virtual void                                        close_display                   (void);

        /// Returns the width of the screen in pixels
        /// \return width of screen in pixels
        virtual uint32_t                                      screen_width                    (void);

        /// Returns the height of the screen in pixels
        /// \return height of screen in pixels
        virtual uint32_t                                      screen_height                   (void);

        /// Returns the aspect ratio of the screen in pixels
        /// \return aspect ratio of screen in pixels
        virtual DTfloat                                     screen_aspect                   (void);


        /// Returns the current viewport
        /// \param x x
        /// \param y y
        /// \param width width
        /// \param height height
        virtual void                                        viewport                        (int32_t &x, int32_t &y, int32_t &width, int32_t &height);

        /// Sets the current viewport
        /// \param x x
        /// \param y y
        /// \param width width
        /// \param height height
        /// \param rt_width width of render target. Needed for compatibility with D3D. 0 for screen dimensions
        /// \param rt_height height of render target. Needed for compatibility with D3D. 0 for screen dimensions
        virtual void                                        set_viewport                    (int32_t x, int32_t y, int32_t width, int32_t height, int32_t rt_width, int32_t rt_height);

        /// Returns the current viewport width
        /// \return viewport width
        virtual uint32_t                                      viewport_width                  (void);

        /// Returns the current viewport height
        /// \return viewport height
        virtual uint32_t                                      viewport_height                 (void);

        /// Returns the current viewport aspect ratio
        /// \return viewport aspect ratio
        virtual DTfloat                                     viewport_aspect                 (void);



        /// Clears the viewport
        virtual void                                        clear_viewport                  (bool depth, bool color, bool stencil);


        /// Viewport clear values
        virtual void                                        clear_stencil_value             (uint32_t s);
        virtual void                                        clear_color_value               (const Color4f &c);
        virtual void                                        clear_depth_value               (DTfloat d);


        //
        // Depth Stencil State
        //

        virtual std::shared_ptr<DT3GLDepthStencilResource>  create_depth_stencil_state      (const DT3GLDepthStencilState &state);
        virtual void                                        set_stencil_ref                 (uint32_t ref);

        //
        // Blend State
        //

        virtual std::shared_ptr<DT3GLBlendResource>         create_blend_state              (const DT3GLBlendState &state);

        //
        // Rasterizer State
        //

        virtual std::shared_ptr<DT3GLRasterizerResource>    create_rasterizer_state         (const DT3GLRasterizerState &state);

        //
        // Sampler State
        //

        virtual std::shared_ptr<DT3GLSamplerResource>       create_sampler_state            (const DT3GLSamplerState &state);

        //
        // Textures
        //

        virtual std::shared_ptr<DT3GLTexture2DResource>     create_texture_2D               (int32_t width, int32_t height, uint8_t *textels, DT3GLTextelFormat format, bool mipmapped, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);
        virtual void                                        update_texture_2D               (const std::shared_ptr<DT3GLTexture2DResource> &res, int32_t x, int32_t y, int32_t width, int32_t height, uint8_t *textels);

        virtual std::shared_ptr<DT3GLTexture3DResource>     create_texture_3D               (int32_t width, int32_t height, int32_t depth, uint8_t *textels, DT3GLTextelFormat format, bool mipmapped, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);
        virtual void                                        update_texture_3D               (const std::shared_ptr<DT3GLTexture3DResource> &res, int32_t x, int32_t y, int32_t z, int32_t width, int32_t height, int32_t depth, uint8_t *textels);

        virtual std::shared_ptr<DT3GLTextureCubeResource>   create_texture_cube             (   int32_t width, int32_t height,
                                                                                                uint8_t *textels_front,
                                                                                                uint8_t *textels_back,
                                                                                                uint8_t *textels_left,
                                                                                                uint8_t *textels_right,
                                                                                                uint8_t *textels_top,
                                                                                                uint8_t *textels_bottom,
                                                                                                DT3GLTextelFormat format,
                                                                                                bool mipmapped,
                                                                                                uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);
        virtual void                                        update_texture_cube             (   const std::shared_ptr<DT3GLTextureCubeResource> &res, int32_t x, int32_t y, int32_t width, int32_t height,
                                                                                                uint8_t *textels_front,
                                                                                                uint8_t *textels_back,
                                                                                                uint8_t *textels_left,
                                                                                                uint8_t *textels_right,
                                                                                                uint8_t *textels_top,
                                                                                                uint8_t *textels_bottom);

        //
        // Buffers
        //

        virtual std::shared_ptr<DT3GLAttribBufferResource>  create_buffer                   (uint8_t *buffer_data, DTsize buffer_size, DT3GLBufferFormat buffer_format, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);
        virtual void                                        update_buffer                   (const std::shared_ptr<DT3GLAttribBufferResource> &res, uint8_t *buffer_data, DTsize buffer_size, DTsize buffer_offset);

        virtual std::shared_ptr<DT3GLElementBufferResource> create_index_buffer             (uint8_t *buffer_data, DTsize buffer_size, DT3GLBufferFormat buffer_format, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);
        virtual void                                        update_index_buffer             (const std::shared_ptr<DT3GLElementBufferResource> &res, uint8_t *buffer_data, DTsize buffer_size, DTsize buffer_offset);

        //
        // Uniforms
        //

        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const int32_t buffer_data);
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const Vector4 &buffer_data);
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const std::vector<Vector4> &buffer_data);
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const Matrix4 &buffer_data);
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const std::vector<Matrix4> &buffer_data);
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const Color4f &buffer_data);

        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const int32_t buffer_data);
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const Vector4 &buffer_data);
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const std::vector<Vector4> &buffer_data);
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const Matrix4 &buffer_data);
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const std::vector<Matrix4> &buffer_data);
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const Color4f &buffer_data);

        //
        // Shaders
        //

        virtual std::shared_ptr<DT3GLShaderResource>        create_shader                   (void);
        virtual void                                        link_shader                     (const std::shared_ptr<DT3GLShaderResource> &shader);

        virtual std::shared_ptr<DT3GLVertexShaderResource>  create_vertex_shader            (const std::string &source);
        virtual std::shared_ptr<DT3GLGeometryShaderResource>create_geometry_shader          (const std::string &source);
        virtual std::shared_ptr<DT3GLFragmentShaderResource>create_fragment_shader          (const std::string &source);

        virtual int32_t                                       attribute_slot                  (const std::shared_ptr<DT3GLShaderResource> &shader, const std::string &name);
        virtual int32_t                                       uniform_slot                    (const std::shared_ptr<DT3GLShaderResource> &shader, const std::string &name);

        //
        // Attachments
        //

        virtual void                                        attach_depth_stencil_state      (const std::shared_ptr<DT3GLDepthStencilResource> &res);
        virtual void                                        attach_blend_state              (const std::shared_ptr<DT3GLBlendResource> &res);
        virtual void                                        attach_rasterizer_state         (const std::shared_ptr<DT3GLRasterizerResource> &res);

        virtual void                                        attach_vertex_shader            (const std::shared_ptr<DT3GLShaderResource> &shader, const std::shared_ptr<DT3GLVertexShaderResource> &vertex_shader);
        virtual void                                        attach_geometry_shader          (const std::shared_ptr<DT3GLShaderResource> &shader, const std::shared_ptr<DT3GLGeometryShaderResource> &geometry_shader);
        virtual void                                        attach_fragment_shader          (const std::shared_ptr<DT3GLShaderResource> &shader, const std::shared_ptr<DT3GLFragmentShaderResource> &fragment_shader);
        virtual void                                        attach_attribute_buffer         (const std::shared_ptr<DT3GLShaderResource> &shader, uint32_t attribute_slot, const std::shared_ptr<DT3GLAttribBufferResource> &res);
        virtual void                                        attach_uniform_buffer           (const std::shared_ptr<DT3GLShaderResource> &shader, uint32_t uniform_slot, const std::shared_ptr<DT3GLUniformResource> &res);

        virtual void                                        attach_shader                   (std::shared_ptr<DT3GLShaderResource> shader);

        virtual void                                        attach_sampler                  (uint32_t texture_slot, const std::shared_ptr<DT3GLSamplerResource> &res);
        virtual void                                        attach_texture                  (uint32_t texture_slot, const std::shared_ptr<DT3GLTexture2DResource> &res);
        virtual void                                        attach_texture                  (uint32_t texture_slot, const std::shared_ptr<DT3GLTexture3DResource> &res);
        virtual void                                        attach_texture                  (uint32_t texture_slot, const std::shared_ptr<DT3GLTextureCubeResource> &res);

        //
        // Drawing
        //

        virtual void                                        draw_arrays                     (DT3GLPrimitiveType primitive_type, uint32_t num_elements);
        virtual void                                        draw_arrays_ranged              (DT3GLPrimitiveType primitive_type, uint32_t start_element, uint32_t num_elements);
        virtual void                                        draw_indexed_arrays             (const std::shared_ptr<DT3GLElementBufferResource> &elements, DT3GLPrimitiveType primitive_type, uint32_t num_elements);

        //
        // Framebuffers
        //

        virtual std::shared_ptr<DT3GLFramebufferResource>   create_framebuffer              (void);
        virtual void                                        activate_framebuffer            (const std::shared_ptr<DT3GLFramebufferResource> &framebuffer);

        virtual void                                        attach_framebuffer_color        (const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, const std::shared_ptr<DT3GLTexture2DResource> &tex, uint32_t target_index = 0);
        virtual void                                        attach_framebuffer_depth_stencil(const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, const std::shared_ptr<DT3GLTexture2DResource> &tex);

        virtual void                                        attach_renderbuffer_color       (const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, int32_t width, int32_t height, DT3GLRenderBufferFormat format, uint32_t target_index = 0);
        virtual void                                        attach_renderbuffer_depth_stencil(const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, int32_t width, int32_t height, DT3GLRenderBufferFormat format);


        /// Copies the current screen to a TextureResource2D
        /// \param tex destination texture
        /// \param rect source rectangle
        virtual void                                        screenshot                      (const std::shared_ptr<TextureResource2D> &tex, const Rectangle &rect);

        //
        // Performance Queries
        //

        virtual void                                        begin_frame                     (void);
        virtual void                                        end_frame                       (void);
        virtual DTdouble                                    perf_lag                        (void);


    private:
        uint32_t                                              textel_byte_size                (DT3GLTextelFormat format);
        void                                                sync_state                      (void);

        uint32_t                                              _width;
        uint32_t                                              _height;

        uint32_t                                              _viewport_x;
        uint32_t                                              _viewport_y;
        uint32_t                                              _viewport_width;
        uint32_t                                              _viewport_height;

        int32_t                                               _default_framebuffer;

        uint32_t                                              _use_stamp;


        // All states
        std::map<uint32_t, std::shared_ptr<DT3GLDepthStencilResource>>    _depth_stencil_states;
        std::map<uint32_t, std::shared_ptr<DT3GLBlendResource>>           _blend_states;
        std::map<uint32_t, std::shared_ptr<DT3GLRasterizerResource>>      _rasterizer_states;
        std::map<uint32_t, std::shared_ptr<DT3GLSamplerResource>>         _sampler_states;


        // State
        std::shared_ptr<DT3GLDepthStencilResource>          _current_depth_stencil_state,
                                                            _pending_depth_stencil_state;

        std::shared_ptr<DT3GLBlendResource>                 _current_blend_state,
                                                            _pending_blend_state;

        std::shared_ptr<DT3GLRasterizerResource>            _current_rasterizer_state,
                                                            _pending_rasterizer_state;

        std::shared_ptr<DT3GLSamplerResource>               _current_sampler_state[16],
                                                            _pending_sampler_state[16];


        std::shared_ptr<DT3GLShaderResource>                _current_shader_state,
                                                            _pending_shader_state;


        std::shared_ptr<DT3GLTexture2DResource>             _current_texture_2d_state[16],
                                                            _pending_texture_2d_state[16];

        std::shared_ptr<DT3GLTexture3DResource>             _current_texture_3d_state[16],
                                                            _pending_texture_3d_state[16];

        std::shared_ptr<DT3GLTextureCubeResource>           _current_texture_cube_state[16],
                                                            _pending_texture_cube_state[16];

        // Not part of any state
        uint32_t                                              _current_stencil_ref,
                                                            _pending_stencil_ref;

        Matrix4                                             _current_texture_matrix[16],
                                                            _pending_texture_matrix[16];

//        // Performance query for frame lag
//        GLuint                                              _frame_lag_query;
//        bool                                           _frame_query_in_progress;
//        int64_t                                             _frame_lag_now;
//        int64_t                                             _frame_lag_last_calculated;
};

//==============================================================================
//==============================================================================

} // DT3

#endif
