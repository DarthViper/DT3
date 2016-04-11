#pragma once
#ifndef DT3_BINARYFILESTREAM
#define DT3_BINARYFILESTREAM
//==============================================================================
///
///    File: BinaryFileStream.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/FileBuffer/BinaryStream.hpp"
#include <memory>
#include <string>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class FilePath;
class FileHandle;
class Progress;

//==============================================================================
/// Class
//==============================================================================

class BinaryFileStream: public BinaryStream {
    public:
        DEFINE_TYPE(BinaryFileStream,BinaryStream)
        DEFINE_CREATE

                                            BinaryFileStream    (void);
        explicit                            BinaryFileStream    (const FilePath &pathname);

    private:
                                            BinaryFileStream    (const BinaryFileStream &rhs);
        BinaryFileStream &                  operator =            (const BinaryFileStream &rhs);

    public:
        virtual                             ~BinaryFileStream    (void);

    public:
        Stream&                             operator<<            (const Stream::FS) override    {    return *this;    }
        Stream&                             operator<<            (const bool n) override;
        Stream&                             operator<<            (const int8_t n) override;
        Stream&                             operator<<            (const int16_t n) override;
        Stream&                             operator<<            (const int32_t n) override;
        Stream&                             operator<<            (const uint8_t n) override;
        Stream&                             operator<<            (const uint16_t n) override;
        Stream&                             operator<<            (const uint32_t n) override;
        Stream&                             operator<<            (const int64_t n) override;
        Stream&                             operator<<            (const uint64_t n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
        Stream&                             operator<<            (const DTsize n) override;
#endif
        Stream&                             operator<<            (const DTfloat n) override;
        Stream&                             operator<<            (const DTdouble n) override;
        Stream&                             operator<<            (const DTlonglong n) override;
        Stream&                             operator<<            (const DTcharacter n) override;
        Stream&                             operator<<            (const char* n) override;
        Stream&                             operator<<            (const std::string &n) override;
        Stream&                             operator<<            (const Stream& n);


        Stream&                             operator>>            (bool &n) override;
        Stream&                             operator>>            (int8_t &n) override;
        Stream&                             operator>>            (int16_t &n) override;
        Stream&                             operator>>            (int32_t &n) override;
        Stream&                             operator>>            (uint8_t &n) override;
        Stream&                             operator>>            (uint16_t &n) override;
        Stream&                             operator>>            (uint32_t &n) override;
        Stream&                             operator>>            (int64_t &n) override;
        Stream&                             operator>>            (uint64_t &n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
        Stream&                             operator>>            (DTsize &n) override;
#endif
        Stream&                             operator>>            (DTfloat &n) override;
        Stream&                             operator>>            (DTdouble &n) override;
        Stream&                             operator>>            (DTlonglong &n) override;
        Stream&                             operator>>            (DTcharacter &n) override;
        Stream&                             operator>>            (std::string &n) override;


        /// Read data into a binary buffer
        /// \param data pointer to buffer
        /// \param size size to read
        /// \return size actually read
        DTsize                              read_raw            (uint8_t *data, DTsize size);

        /// Write data from a binary buffer
        /// \param data pointer to buffer
        /// \param size size to read
        void                                write_raw            (uint8_t *data, DTsize size);

        /// Return write position
        /// \return write position
        DTsize                              p                   (void) override;

        /// Return read position
        /// \return read position
        DTsize                              g                   (void) override;

        /// Change write position
        /// \param p position
        /// \param r relative
        void                                seek_p              (DToffset p, Relative r) override;

        /// Change read position
        /// \param p position
        /// \param r relative
        void                                seek_g              (DToffset g, Relative r) override;


        /// Checks for end of file
        /// \return End of file
        bool                           is_eof                (void);

        /// Clears end of file flag
        void                                clear_EOF            (void)                  {   _eof = false;   }

        /// Associate the file handle with the stream. This opens a fragment of a file.
        /// \param file file handle
        /// \param start start of the fragment
        /// \param length length of the fragment
        /// \param progress progress
        void                                open_file_fragment  (const std::shared_ptr<FileHandle> &file, DTsize start, DTsize length, std::shared_ptr<Progress> progress = NULL);

        /// Close the stream
        void                                close                (void);

        /// Length of the stream
        /// \return Length of the stream
        DTsize                              length              (void) const            {    return _length;        }

        /// Returns the start of the stream if opening a fragment
        /// \return Start position
        DTsize                              start               (void) const            {    return _start;        }

        /// Returns the file handle associated with the stream
        /// \return file handle
        const std::shared_ptr<FileHandle>&  file_handle         (void) const;

        /// Sets the file handle associated with the stream
        /// \param file_handle File handle
        void                                set_file_handle        (const std::shared_ptr<FileHandle> &file_handle);

    private:
        std::shared_ptr<FileHandle>         _file;

        DTsize                              _start;
        DTsize                              _length;
        DTsize                              _last_update;

        std::shared_ptr<Progress>           _progress;

        bool                           _eof;
};

//==============================================================================
//==============================================================================


} // DT3

#endif
