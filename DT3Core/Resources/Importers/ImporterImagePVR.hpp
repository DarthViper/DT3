#pragma once
#ifndef DT3_IMPORTERIMAGEPVR
#define DT3_IMPORTERIMAGEPVR
//==============================================================================
///
///    File: ImporterImagePVR.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Resources/Importers/ImporterImage.hpp"
#include "DT3Core/Devices/DeviceGraphics.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class FilePath;
class BinaryFileStream;

//==============================================================================
/// Class
//==============================================================================

class ImporterImagePVR: public ImporterImage {
    public:
        DEFINE_TYPE(ImporterImagePVR,ImporterImage)
        DEFINE_CREATE

                                    ImporterImagePVR    (void);

    private:
                                    ImporterImagePVR    (const ImporterImagePVR &rhs);
        ImporterImagePVR &          operator =            (const ImporterImagePVR &rhs);

    public:
        virtual                        ~ImporterImagePVR    (void);

    public:
        /// Imports an image into a TextureResource2D
        /// \param target object to import texture into
        /// \param args arguments to importer
        /// \return error code
        virtual DTerr                import                (TextureResource2D *target, std::string args) override;

        /// Imports an image into a TextureResource3D
        /// \param target object to import texture into
        /// \param args arguments to importer
        /// \return error code
        virtual DTerr                import                (TextureResource3D *target, std::string args) override;

        /// Imports an image into a TextureResourceCube
        /// \param target object to import texture into
        /// \param args arguments to importer
        /// \return error code
        virtual DTerr                import                (TextureResourceCube *target, std::string args) override;

    private:
        DTerr                       import              (   const FilePath &pathname,
                                                            const std::string &args,
                                                            uint32_t &width,
                                                            uint32_t &height,
                                                            std::shared_ptr<uint8_t> &data,
                                                            DT3GLTextelFormat &format);

        // From Apple sample code
        enum {
            kPVRTextureFlagTypePVR_2 = 24,
            kPVRTextureFlagTypePVR_4
        };

        struct PVRTexHeader {
            uint32_t headerLength;
            uint32_t height;
            uint32_t width;
            uint32_t numMipmaps;
            uint32_t flags;
            uint32_t dataLength;
            uint32_t bpp;
            uint32_t bitmaskRed;
            uint32_t bitmaskGreen;
            uint32_t bitmaskBlue;
            uint32_t bitmaskAlpha;
            uint32_t pvrTag;
            uint32_t numSurfs;
        };
};

//==============================================================================
//==============================================================================

} // DT3

#endif
