#pragma once
//==============================================================================
///
///	File: TextureResourceCube.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Resources/ResourceTypes/Resource.hpp"
#include "DT3Core/Types/Math/Color4b.hpp"
#include "DT3Core/Devices/DeviceGraphics.hpp"
#include <vector>
#include <string>
#include <map>
#include <mutex>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================



//==============================================================================
/// Texture resource type
//==============================================================================

class TextureResourceCube: public Resource {
    public:
        DEFINE_TYPE(TextureResourceCube,Resource)
        DEFINE_CREATE

                                    TextureResourceCube (void);
    private:
                                    TextureResourceCube (const TextureResourceCube &rhs);
        TextureResourceCube &       operator =			(const TextureResourceCube &rhs);
    public:
        virtual						~TextureResourceCube(void);

    public:
        /// Called to initialize the class
        static void                 initialize_static   (void);

        /// Called to uninitialize the class
        static void                 uninitialize_static (void);

        /// Import the resource with an importer into a platform independent format
        /// \param pathname path to resource
        /// \param args importer args
        /// \return error code
        DTerr						import				(const FilePath &pathname, std::string args);

        // Texture building functions

        /// Allocate a Cubemap texture
        /// \param width width of texture
        /// \param height height of texture
        /// \param depth depth of texture
        /// \param textels_front textels_front data (can be NULL)
        /// \param textels_back textels_back data (can be NULL)
        /// \param textels_left textels_left data (can be NULL)
        /// \param textels_right textels_right data (can be NULL)
        /// \param textels_top textels_top data (can be NULL)
        /// \param textels_bottom textels_bottom data (can be NULL)
        /// \param format format
        /// \param mipmapped mipmapped
        void                        set_textels_cube    (   const int32_t width, const int32_t height,
                                                            const std::shared_ptr<uint8_t> &textels_front,
                                                            const std::shared_ptr<uint8_t> &textels_back,
                                                            const std::shared_ptr<uint8_t> &textels_left,
                                                            const std::shared_ptr<uint8_t> &textels_right,
                                                            const std::shared_ptr<uint8_t> &textels_top,
                                                            const std::shared_ptr<uint8_t> &textels_bottom,
                                                            DT3GLTextelFormat format,
                                                            bool mipmapped,
                                                            uint32_t flags = DT3GL_ACCESS_CPU_NONE | DT3GL_ACCESS_GPU_READ);

        /// Width of the buffer
        /// \return buffer width
        int32_t						width               (void) const	{	return _width;	}

        /// Height of the buffer
        /// \return buffer height
        int32_t						height              (void) const	{	return _height;	}

        /// Activate the resource
        /// \param texture_slot which slot to activate the texture in
        void                        activate            (uint32_t texture_slot);

        /// Load the resource
        /// \param pathname path to file
        /// \param args arguments to importer
        /// \return resource
        static std::shared_ptr<TextureResourceCube>    import_resource (const FilePath &pathname, std::string args = "");

    private:
        static std::mutex                                                   _texture_map_lock;
        static std::map<std::string, std::shared_ptr<TextureResourceCube>>  _texture_map;

        static void                 reload_if_changed   (void);

        void                        screen_opened       (uint32_t width, uint32_t height);
        void                        screen_closed       (void);

        // Data for Cube Maps
        std::shared_ptr<uint8_t>                    _textels_front;
        std::shared_ptr<uint8_t>                    _textels_back;
        std::shared_ptr<uint8_t>                    _textels_left;
        std::shared_ptr<uint8_t>                    _textels_right;
        std::shared_ptr<uint8_t>                    _textels_top;
        std::shared_ptr<uint8_t>                    _textels_bottom;

        DT3GLTextelFormat                            _format;

        int32_t                                       _width;
        int32_t                                       _height;

        bool                                   _mipmapped;
        uint32_t                                      _flags;

        std::shared_ptr<DT3GLTextureCubeResource>   _resource_cube;
};

//==============================================================================
/// Streaming operators
//==============================================================================

Stream& operator <<(Stream &s, const std::shared_ptr<TextureResourceCube> &r);
Stream& operator >>(Stream &s, std::shared_ptr<TextureResourceCube> &r);

//==============================================================================
//==============================================================================

} // DT3
