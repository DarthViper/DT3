#pragma once
#ifndef DT3_DEVICEGRAPHICS
#define DT3_DEVICEGRAPHICS
//==============================================================================
///
///	File: DeviceGraphics.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Math/Color4f.hpp"
#include "DT3Core/Types/Math/Rectangle.hpp"
#include "DT3Core/Types/Math/Vector4.hpp"
#include "DT3Core/Types/Math/Matrix4.hpp"
#include "DT3Core/Types/Utility/LatentCall.hpp"
#include "DT3Core/Devices/DeviceBase.hpp"
#include <vector>
#include <memory>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward Declarations
//==============================================================================

class TextureResource2D;
class GeometryResource;
class MaterialResource;
class Particles;
class CameraObject;
class Color4b;

//==============================================================================
//==============================================================================

enum DT3GLAccessFlags {
    DT3GL_ACCESS_CPU_NONE = 0,
    DT3GL_ACCESS_CPU_READ = 1<<1,
    DT3GL_ACCESS_CPU_WRITE = 1<<2,

    DT3GL_ACCESS_GPU_NONE = 0,
    DT3GL_ACCESS_GPU_READ = 1<<3,
    DT3GL_ACCESS_GPU_WRITE = 1<<4
};

enum DT3GLComparison {
    DT3GL_COMPARE_ALWAYS,
    DT3GL_COMPARE_NEVER,
    DT3GL_COMPARE_EQUAL,
    DT3GL_COMPARE_NOTEQUAL,
    DT3GL_COMPARE_GREATER,
    DT3GL_COMPARE_GEQUAL,
    DT3GL_COMPARE_LESS,
    DT3GL_COMPARE_LEQUAL
};

enum DT3GLStencilOp {
    DT3GL_STENCILOP_KEEP,
    DT3GL_STENCILOP_ZERO,
    DT3GL_STENCILOP_REPLACE,
    DT3GL_STENCILOP_INCR,
    DT3GL_STENCILOP_DECR,
    DT3GL_STENCILOP_INCR_WRAP,
    DT3GL_STENCILOP_DECR_WRAP,
    DT3GL_STENCILOP_INVERT
};

enum DT3GLBlend {
    DT3GL_BLEND_ZERO,
    DT3GL_BLEND_ONE,
    DT3GL_BLEND_SRC_ALPHA,
    DT3GL_BLEND_ONE_MINUS_SRC_ALPHA,
    DT3GL_BLEND_DST_ALPHA,
    DT3GL_BLEND_ONE_MINUS_DST_ALPHA,
    DT3GL_BLEND_SRC_COLOR,
    DT3GL_BLEND_DST_COLOR,
    DT3GL_BLEND_ONE_MINUS_SRC_COLOR,
    DT3GL_BLEND_ONE_MINUS_DST_COLOR
};

enum DT3GLCullMode {
    DT3GL_CULL_FRONT,
    DT3GL_CULL_BACK,
    DT3GL_CULL_NONE
};

enum DT3GLFilterMode {
    DT3GL_FILTER_NEAREST,
    DT3GL_FILTER_LINEAR,
    DT3GL_FILTER_NEAREST_MIPMAP,
    DT3GL_FILTER_LINEAR_MIPMAP
};

enum DT3GLAddressMode {
    DT3GL_ADDRESS_REPEAT,
    DT3GL_ADDRESS_CLAMP_TO_EDGE
};

enum DT3GLTextelFormat {
    DT3GL_FORMAT_RGBA,
    DT3GL_FORMAT_RGBA_5551,
    DT3GL_FORMAT_RGBA_4444,
    DT3GL_FORMAT_RGB,
    DT3GL_FORMAT_RGB_565,
    DT3GL_FORMAT_RGBA_HALF_FLOAT,
    DT3GL_FORMAT_LUM_8,
    DT3GL_FORMAT_BGRA,

#if DT3_OS == DT3_IOS || DT3_OS == DT3_ANDROID
    DT3GL_FORMAT_PVR2_RGBA,
    DT3GL_FORMAT_PVR4_RGBA,
    DT3GL_FORMAT_PVR2_RGB,
    DT3GL_FORMAT_PVR4_RGB,
#endif

    DT3GL_FORMAT_DEPTH_16,
    DT3GL_FORMAT_DEPTH_24,
    DT3GL_FORMAT_DEPTH_24_STENCIL_8,

    DT3GL_FORMAT_UNKNOWN
};

enum DT3GLRenderBufferFormat {
    DT3GL_RB_FORMAT_NONE,
    DT3GL_RB_FORMAT_RGBA8,
    DT3GL_RB_FORMAT_DEPTH_16,
    DT3GL_RB_FORMAT_DEPTH_24,
    DT3GL_RB_FORMAT_DEPTH_24_STENCIL_8
};

enum DT3GLBufferFormat {
    DT3GL_BUFFER_FORMAT_2_FLOAT,
    DT3GL_BUFFER_FORMAT_3_FLOAT,
    DT3GL_BUFFER_FORMAT_4_FLOAT,
    DT3GL_BUFFER_FORMAT_4_UBYTE,
    DT3GL_BUFFER_FORMAT_4_USHORT,
    DT3GL_BUFFER_FORMAT_1_UINT
};

enum DT3GLUniformFormat {
    DT3GL_UNIFORM_FORMAT_1_INT,
    DT3GL_UNIFORM_FORMAT_4_FLOAT,
    DT3GL_UNIFORM_FORMAT_16_FLOAT
};

enum DT3GLConstantFormat {

};

enum DT3GLPixelFormat {

};

enum DT3GLDepthStencilFormat {

};

enum DT3GLPrimitiveType {
    DT3GL_PRIM_TRIS,
    DT3GL_PRIM_TRI_STRIP,
    DT3GL_PRIM_LINE_LOOP,
    DT3GL_PRIM_LINES
};

//==============================================================================
//==============================================================================

//
// Depth Stencil State
//

struct DT3GLDepthStencilState {
    bool           depth_enable;
    bool           depth_write_mask;
    DT3GLComparison     depth_func;

    bool           stencil_enable;
    uint32_t              stencil_read_mask;
    uint32_t              stencil_write_mask;

    DT3GLStencilOp      front_face_stencil_fail_op;
    DT3GLStencilOp      front_face_stencil_depth_fail_op;
    DT3GLStencilOp      front_face_stencil_pass_op;
    DT3GLComparison     front_face_stencil_func;

    DT3GLStencilOp      back_face_stencil_fail_op;
    DT3GLStencilOp      back_face_stencil_depth_fail_op;
    DT3GLStencilOp      back_face_stencil_pass_op;
    DT3GLComparison     back_face_stencil_func;
};

//
// Blend State
//

struct DT3GLBlendState {
    bool           blend_enable;
    DT3GLBlend          src_blend;
    DT3GLBlend          dest_blend;
    DT3GLBlend          src_blend_alpha;
    DT3GLBlend          dest_blend_alpha;
    bool           render_target_write_mask_r;
    bool           render_target_write_mask_g;
    bool           render_target_write_mask_b;
    bool           render_target_write_mask_a;
};

//
// Rasterizer State
//

struct DT3GLRasterizerState {
    DT3GLCullMode       cull_mode;
    DTfloat             depth_bias;
    DTfloat             slope_scaled_depth_bias;
    DTfloat             depth_bias_clamp;
    bool           scissor_enable;
};

//
// Sampler State
//

struct DT3GLSamplerState {
    DT3GLFilterMode     filter;
    DT3GLAddressMode	address_u;
    DT3GLAddressMode	address_v;
    DT3GLAddressMode	address_w;
    DTfloat             mip_lod_bias;
    DTfloat             max_anisotropy;
};

//==============================================================================
//==============================================================================

enum DT3GLStandardAttrib {
    DT3GL_ATTRIB_NONE = -1,
    DT3GL_ATTRIB_POSITION = 0,
    DT3GL_ATTRIB_NORMAL,
    DT3GL_ATTRIB_TEXCOORD0,
    DT3GL_ATTRIB_TEXCOORD1,
    DT3GL_ATTRIB_COLOR,
    DT3GL_ATTRIB_TANGENT,

    DT3GL_ATTRIB_NUM
};

enum DT3GLStandardUniform {
    DT3GL_UNIFORM_NONE = -1,
    DT3GL_UNIFORM_MODELVIEW = 0,
    DT3GL_UNIFORM_PROJECTION,
    DT3GL_UNIFORM_TEX0,
    DT3GL_UNIFORM_TEX1,
    DT3GL_UNIFORM_TEX2,
    DT3GL_UNIFORM_TEX3,
    DT3GL_UNIFORM_TEX4,
    DT3GL_UNIFORM_TEX5,
    DT3GL_UNIFORM_TEX6,
    DT3GL_UNIFORM_TEX7,
    DT3GL_UNIFORM_TEX8,
    DT3GL_UNIFORM_TEX9,
    DT3GL_UNIFORM_TEX10,
    DT3GL_UNIFORM_TEX11,
    DT3GL_UNIFORM_TEX12,
    DT3GL_UNIFORM_TEX13,
    DT3GL_UNIFORM_TEX14,
    DT3GL_UNIFORM_TEX15,
    DT3GL_UNIFORM_TEX_MATRIX0,
    DT3GL_UNIFORM_TEX_MATRIX1,
    DT3GL_UNIFORM_TEX_MATRIX2,
    DT3GL_UNIFORM_TEX_MATRIX3,
    DT3GL_UNIFORM_TEX_MATRIX4,
    DT3GL_UNIFORM_TEX_MATRIX5,
    DT3GL_UNIFORM_TEX_MATRIX6,
    DT3GL_UNIFORM_TEX_MATRIX7,
    DT3GL_UNIFORM_TEX_MATRIX8,
    DT3GL_UNIFORM_TEX_MATRIX9,
    DT3GL_UNIFORM_TEX_MATRIX10,
    DT3GL_UNIFORM_TEX_MATRIX11,
    DT3GL_UNIFORM_TEX_MATRIX12,
    DT3GL_UNIFORM_TEX_MATRIX13,
    DT3GL_UNIFORM_TEX_MATRIX14,
    DT3GL_UNIFORM_TEX_MATRIX15,

    DT3GL_UNIFORM_NUM
};

//==============================================================================
//==============================================================================

class DT3GLDepthStencilResource {
    public:
                    DT3GLDepthStencilResource       (void)  {}
        virtual     ~DT3GLDepthStencilResource      (void)  {}
};

class DT3GLBlendResource {
    public:
                    DT3GLBlendResource              (void)  {}
        virtual     ~DT3GLBlendResource             (void)  {}
};

class DT3GLRasterizerResource {
    public:
                    DT3GLRasterizerResource         (void)  {}
        virtual     ~DT3GLRasterizerResource        (void)  {}
};

class DT3GLSamplerResource {
    public:
                    DT3GLSamplerResource            (void)  {}
        virtual     ~DT3GLSamplerResource           (void)  {}
};

//==============================================================================
//==============================================================================

class DT3GLTexture2DResource {
    public:
                    DT3GLTexture2DResource          (void)  {}
        virtual     ~DT3GLTexture2DResource         (void)  {}
};

class DT3GLTexture3DResource {
    public:
                    DT3GLTexture3DResource          (void)  {}
        virtual     ~DT3GLTexture3DResource         (void)  {}
};

class DT3GLTextureCubeResource {
    public:
                    DT3GLTextureCubeResource        (void)  {}
        virtual     ~DT3GLTextureCubeResource       (void)  {}
};

//==============================================================================
//==============================================================================

class DT3GLAttribBufferResource {
    public:
                    DT3GLAttribBufferResource       (void)  {}
        virtual     ~DT3GLAttribBufferResource      (void)  {}
};

class DT3GLElementBufferResource {
    public:
                    DT3GLElementBufferResource      (void)  {}
        virtual     ~DT3GLElementBufferResource     (void)  {}
};

class DT3GLUniformResource {
    public:
                    DT3GLUniformResource            (void)  {}
        virtual     ~DT3GLUniformResource           (void)  {}
};

//==============================================================================
//==============================================================================

class DT3GLShaderResource {
    public:
                    DT3GLShaderResource             (void)  {}
        virtual     ~DT3GLShaderResource            (void)  {}
};

class DT3GLVertexShaderResource {
    public:
                    DT3GLVertexShaderResource       (void)  {}
        virtual     ~DT3GLVertexShaderResource      (void)  {}
};

class DT3GLGeometryShaderResource {
    public:
                    DT3GLGeometryShaderResource     (void)  {}
        virtual     ~DT3GLGeometryShaderResource    (void)  {}
};

class DT3GLFragmentShaderResource {
    public:
                    DT3GLFragmentShaderResource     (void)  {}
        virtual     ~DT3GLFragmentShaderResource    (void)  {}
};

//==============================================================================
//==============================================================================

class DT3GLFramebufferResource {
    public:
                    DT3GLFramebufferResource        (void)  {}
        virtual     ~DT3GLFramebufferResource       (void)  {}
};

//==============================================================================
/// Class
//==============================================================================

class DeviceGraphics: public DeviceBase {
        /// Base class for Renderer.

    public:
        DEFINE_TYPE(DeviceGraphics,DeviceBase)
        //DEFINE_CREATE

                                DeviceGraphics                  (void);
    private:
                                DeviceGraphics                  (const DeviceGraphics&);
        DeviceGraphics &        operator =                      (const DeviceGraphics&);
    public:
        virtual                 ~DeviceGraphics                 (void);

    public:

        /// Screen context is ready
        virtual void                                        init_display                    (void) = 0;

        /// Opens up a display or tells the Device that a new display was opened
        /// \param width width of the display
        /// \param height width of the display
        virtual void                                        open_display                    (int32_t width, int32_t height) = 0;

        /// Changes a display or tells the Device that a display was changed
        /// \param width width of the display
        /// \param height width of the display
        virtual void                                        change_display                  (uint32_t width, uint32_t height) = 0;

        /// Closes a display or tells the Device that a display was closed
        virtual void                                        close_display                   (void) = 0;

        /// Returns the width of the screen in pixels
        /// \return width of screen in pixels
        virtual uint32_t                                      screen_width                    (void) = 0;

        /// Returns the height of the screen in pixels
        /// \return height of screen in pixels
        virtual uint32_t                                      screen_height                   (void) = 0;

        /// Returns the aspect ratio of the screen in pixels
        /// \return aspect ratio of screen in pixels
        virtual DTfloat                                     screen_aspect                   (void) = 0;


        /// Returns the current viewport
        /// \param x x
        /// \param y y
        /// \param width width
        /// \param height height
        virtual void                                        viewport                        (int32_t &x, int32_t &y, int32_t &width, int32_t &height) = 0;

        /// Sets the current viewport
        /// \param x x
        /// \param y y
        /// \param width width
        /// \param height height
        /// \param rt_width width of render target. Needed for compatibility with D3D. 0 for screen dimensions
        /// \param rt_height height of render target. Needed for compatibility with D3D. 0 for screen dimensions
        virtual void                                        set_viewport                    (int32_t x, int32_t y, int32_t width, int32_t height, int32_t rt_width = 0, int32_t rt_height = 0) = 0;

        /// Returns the current viewport width
        /// \return viewport width
        virtual uint32_t                                      viewport_width                  (void) = 0;

        /// Returns the current viewport height
        /// \return viewport height
        virtual uint32_t                                      viewport_height                 (void) = 0;

        /// Returns the current viewport aspect ratio
        /// \return viewport aspect ratio
        virtual DTfloat                                     viewport_aspect                 (void) = 0;



        /// Clears the viewport
        virtual void                                        clear_viewport                  (bool depth, bool color, bool stencil) = 0;


        /// Viewport clear values
        virtual void                                        clear_stencil_value             (uint32_t s) = 0;
        virtual void                                        clear_color_value               (const Color4f &c) = 0;
        virtual void                                        clear_depth_value               (DTfloat d) = 0;

        //
        // Depth Stencil State
        //

        virtual std::shared_ptr<DT3GLDepthStencilResource>  create_depth_stencil_state      (const DT3GLDepthStencilState &state) = 0;
        virtual void                                        set_stencil_ref                 (uint32_t ref) = 0;

        //
        // Blend State
        //

        virtual std::shared_ptr<DT3GLBlendResource>         create_blend_state              (const DT3GLBlendState &state) = 0;

        //
        // Rasterizer State
        //

        virtual std::shared_ptr<DT3GLRasterizerResource>    create_rasterizer_state         (const DT3GLRasterizerState &state) = 0;

        //
        // Sampler State
        //

        virtual std::shared_ptr<DT3GLSamplerResource>       create_sampler_state            (const DT3GLSamplerState &state) = 0;

        //
        // Textures
        //

        virtual std::shared_ptr<DT3GLTexture2DResource>     create_texture_2D               (int32_t width, int32_t height, uint8_t *textels, DT3GLTextelFormat format, bool mipmapped, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ) = 0;
        virtual void                                        update_texture_2D               (const std::shared_ptr<DT3GLTexture2DResource> &res, int32_t x, int32_t y, int32_t width, int32_t height, uint8_t *textels) = 0;

        virtual std::shared_ptr<DT3GLTexture3DResource>     create_texture_3D               (int32_t width, int32_t height, int32_t depth, uint8_t *textels, DT3GLTextelFormat format, bool mipmapped, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ) = 0;
        virtual void                                        update_texture_3D               (const std::shared_ptr<DT3GLTexture3DResource> &res, int32_t x, int32_t y, int32_t z, int32_t width, int32_t height, int32_t depth, uint8_t *textels) = 0;

        virtual std::shared_ptr<DT3GLTextureCubeResource>   create_texture_cube             (   int32_t width, int32_t height,
                                                                                                uint8_t *textels_front,
                                                                                                uint8_t *textels_back,
                                                                                                uint8_t *textels_left,
                                                                                                uint8_t *textels_right,
                                                                                                uint8_t *textels_top,
                                                                                                uint8_t *textels_bottom,
                                                                                                DT3GLTextelFormat format,
                                                                                                bool mipmapped,
                                                                                                uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ) = 0;
        virtual void                                        update_texture_cube             (   const std::shared_ptr<DT3GLTextureCubeResource> &res, int32_t x, int32_t y, int32_t width, int32_t height,
                                                                                                uint8_t *textels_front,
                                                                                                uint8_t *textels_back,
                                                                                                uint8_t *textels_left,
                                                                                                uint8_t *textels_right,
                                                                                                uint8_t *textels_top,
                                                                                                uint8_t *textels_bottom) = 0;

        //
        // Buffers
        //

        virtual std::shared_ptr<DT3GLAttribBufferResource>  create_buffer                   (uint8_t *buffer_data, DTsize buffer_size, DT3GLBufferFormat buffer_format, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ) = 0;
        virtual void                                        update_buffer                   (const std::shared_ptr<DT3GLAttribBufferResource> &res, uint8_t *buffer_data, DTsize buffer_size, DTsize buffer_offset) = 0;

        virtual std::shared_ptr<DT3GLElementBufferResource> create_index_buffer             (uint8_t *buffer_data, DTsize buffer_size, DT3GLBufferFormat buffer_format, uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ) = 0;
        virtual void                                        update_index_buffer             (const std::shared_ptr<DT3GLElementBufferResource> &res, uint8_t *buffer_data, DTsize buffer_size, DTsize buffer_offset) = 0;

        //
        // Uniforms
        //

        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const int32_t buffer_data) = 0;
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const Vector4 &buffer_data) = 0;
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const std::vector<Vector4> &buffer_data) = 0;
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const Matrix4 &buffer_data) = 0;
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const std::vector<Matrix4> &buffer_data) = 0;
        virtual std::shared_ptr<DT3GLUniformResource>       create_uniform                  (const Color4f &buffer_data) = 0;

        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const int32_t buffer_data) = 0;
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const Vector4 &buffer_data) = 0;
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const std::vector<Vector4> &buffer_data) = 0;
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const Matrix4 &buffer_data) = 0;
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const std::vector<Matrix4> &buffer_data) = 0;
        virtual void                                        update_uniform                  (const std::shared_ptr<DT3GLUniformResource> &res, const Color4f &buffer_data) = 0;

        //
        // Shaders
        //

        virtual std::shared_ptr<DT3GLShaderResource>        create_shader                   (void) = 0;
        virtual void                                        link_shader                     (const std::shared_ptr<DT3GLShaderResource> &shader) = 0;

        virtual std::shared_ptr<DT3GLVertexShaderResource>  create_vertex_shader            (const std::string &source) = 0;
        virtual std::shared_ptr<DT3GLGeometryShaderResource>create_geometry_shader          (const std::string &source) = 0;
        virtual std::shared_ptr<DT3GLFragmentShaderResource>create_fragment_shader          (const std::string &source) = 0;

        virtual int32_t                                       attribute_slot                  (const std::shared_ptr<DT3GLShaderResource> &shader, const std::string &name) = 0;
        virtual int32_t                                       uniform_slot                    (const std::shared_ptr<DT3GLShaderResource> &shader, const std::string &name) = 0;

        //
        // Attachments
        //

        virtual void                                        attach_depth_stencil_state      (const std::shared_ptr<DT3GLDepthStencilResource> &res) = 0;
        virtual void                                        attach_blend_state              (const std::shared_ptr<DT3GLBlendResource> &res) = 0;
        virtual void                                        attach_rasterizer_state         (const std::shared_ptr<DT3GLRasterizerResource> &res) = 0;

        virtual void                                        attach_vertex_shader            (const std::shared_ptr<DT3GLShaderResource> &shader, const std::shared_ptr<DT3GLVertexShaderResource> &vertex_shader) = 0;
        virtual void                                        attach_geometry_shader          (const std::shared_ptr<DT3GLShaderResource> &shader, const std::shared_ptr<DT3GLGeometryShaderResource> &geometry_shader) = 0;
        virtual void                                        attach_fragment_shader          (const std::shared_ptr<DT3GLShaderResource> &shader, const std::shared_ptr<DT3GLFragmentShaderResource> &fragment_shader) = 0;
        virtual void                                        attach_attribute_buffer         (const std::shared_ptr<DT3GLShaderResource> &shader, uint32_t attribute_slot, const std::shared_ptr<DT3GLAttribBufferResource> &res) = 0;
        virtual void                                        attach_uniform_buffer           (const std::shared_ptr<DT3GLShaderResource> &shader, uint32_t uniform_slot, const std::shared_ptr<DT3GLUniformResource> &res) = 0;

        virtual void                                        attach_shader                   (std::shared_ptr<DT3GLShaderResource> shader) = 0;

        virtual void                                        attach_sampler                  (uint32_t texture_slot, const std::shared_ptr<DT3GLSamplerResource> &res) = 0;
        virtual void                                        attach_texture                  (uint32_t texture_slot, const std::shared_ptr<DT3GLTexture2DResource> &res) = 0;
        virtual void                                        attach_texture                  (uint32_t texture_slot, const std::shared_ptr<DT3GLTexture3DResource> &res) = 0;
        virtual void                                        attach_texture                  (uint32_t texture_slot, const std::shared_ptr<DT3GLTextureCubeResource> &res) = 0;


        //
        // Drawing
        //

        virtual void                                        draw_arrays                     (DT3GLPrimitiveType primitive_type, uint32_t num_elements) = 0;
        virtual void                                        draw_arrays_ranged              (DT3GLPrimitiveType primitive_type, uint32_t start_element, uint32_t num_elements) = 0;
        virtual void                                        draw_indexed_arrays             (const std::shared_ptr<DT3GLElementBufferResource> &elements, DT3GLPrimitiveType primitive_type, uint32_t num_elements) = 0;

        //
        // Framebuffers
        //

        virtual std::shared_ptr<DT3GLFramebufferResource>   create_framebuffer              (void) = 0;
        virtual void                                        activate_framebuffer            (const std::shared_ptr<DT3GLFramebufferResource> &framebuffer) = 0;

        virtual void                                        attach_framebuffer_color        (const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, const std::shared_ptr<DT3GLTexture2DResource> &tex, uint32_t target_index = 0) = 0;
        virtual void                                        attach_framebuffer_depth_stencil(const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, const std::shared_ptr<DT3GLTexture2DResource> &tex) = 0;

        virtual void                                        attach_renderbuffer_color       (const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, int32_t width, int32_t height, DT3GLRenderBufferFormat format, uint32_t target_index = 0) = 0;
        virtual void                                        attach_renderbuffer_depth_stencil(const std::shared_ptr<DT3GLFramebufferResource> &framebuffer, int32_t width, int32_t height, DT3GLRenderBufferFormat format) = 0;

        /// Copies the current screen to a TextureResource2D
        /// \param tex destination texture
        /// \param rect source rectangle
        virtual void                                        screenshot                      (const std::shared_ptr<TextureResource2D> &tex, const Rectangle &rect) = 0;

        //
        // Performance Queries
        //

        virtual void                                        begin_frame                     (void)  {}
        virtual void                                        end_frame                       (void)  {}
        virtual DTdouble                                    perf_lag                        (void)  {   return 0.0; }

        /// Description
        /// \param param description
        /// \return description
        static void                                         reset                           (DT3GLDepthStencilState &s);
        static void                                         reset                           (DT3GLBlendState &s);
        static void                                         reset                           (DT3GLRasterizerState &s);
        static void                                         reset                           (DT3GLSamplerState &s);

};

//==============================================================================
// Info classes for Traits
//==============================================================================

#define DEF_GL_TYPE_TRAITS(T)                                                       \
    template <> struct Info<T> {                                                    \
        static T                    default_value(void)	{	return (T) 0;   }       \
        static const DTcharacter*	name(void)          {	return #T;      }       \
        static const DTcharacter*	name_caps(void)     {	return #T;      }       \
        enum { isFundamental = 0 };                                                 \
    };

namespace TypeTraitsInfo {

    DEF_GL_TYPE_TRAITS(DT3GLAccessFlags)
    DEF_GL_TYPE_TRAITS(DT3GLComparison)
    DEF_GL_TYPE_TRAITS(DT3GLStencilOp)
    DEF_GL_TYPE_TRAITS(DT3GLBlend)
    DEF_GL_TYPE_TRAITS(DT3GLCullMode)
    DEF_GL_TYPE_TRAITS(DT3GLFilterMode)
    DEF_GL_TYPE_TRAITS(DT3GLAddressMode)
    DEF_GL_TYPE_TRAITS(DT3GLTextelFormat)
    DEF_GL_TYPE_TRAITS(DT3GLRenderBufferFormat)
    DEF_GL_TYPE_TRAITS(DT3GLBufferFormat)

    DEF_GL_TYPE_TRAITS(DT3GLUniformFormat)
    DEF_GL_TYPE_TRAITS(DT3GLConstantFormat)
    DEF_GL_TYPE_TRAITS(DT3GLPixelFormat)
    DEF_GL_TYPE_TRAITS(DT3GLDepthStencilFormat)
    DEF_GL_TYPE_TRAITS(DT3GLPrimitiveType)

} // TypeTraitsDefaults

//==============================================================================
//==============================================================================

} // DT3

#endif
