#pragma once
#ifndef DT3_FILEHANDLEUNCOMPRESSEDFD
#define DT3_FILEHANDLEUNCOMPRESSEDFD
//==============================================================================
///
///    File: FileHandleUncompressedFD.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/FileBuffer/FileHandle.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class FilePath;

//==============================================================================
/// Class
//==============================================================================

class FileHandleUncompressedFD: public FileHandle {
    public:
        DEFINE_TYPE(FileHandleUncompressedFD,FileHandle)
        //DEFINE_CREATE_AND_CLONE
        DEFINE_CREATE

                                    FileHandleUncompressedFD    (void);
    private:
                                    FileHandleUncompressedFD    (const FileHandleUncompressedFD &rhs);
        FileHandleUncompressedFD &  operator =                  (const FileHandleUncompressedFD &rhs);
    public:
        virtual                     ~FileHandleUncompressedFD   (void);

    public:
        //
        // File access routines
        //

        /// Opens a file
        /// \param pathname path to file
        /// \param read read or write
        /// \return Error
        virtual DTerr           open_file            (const FilePath &pathname, bool read = true);

        /// Sets an existing file descriptor for file
        /// \param fd file descriptor
        /// \return Error
        virtual DTerr           set_fd              (int32_t fd);

        /// Close the file handle
        virtual void            close                (void) override;

        /// Returns the length of the file
        /// \return Length of the file
        virtual DTsize          length              (void) const override    {    return _length;            }


        /// Return write position
        /// \return write position
        virtual DTsize          p                   (void) override;

        /// Return read position
        /// \return read position
        virtual DTsize          g                   (void) override;

        /// Change write position
        /// \param p position
        /// \param r relative
        virtual void            seek_p                (DToffset p, Relative r) override;

        /// Change read position
        /// \param p position
        /// \param r relative
        virtual void            seek_g                (DToffset g, Relative r) override;


        /// Peeks ahead at the next byte
        /// \return next byte
        virtual DTcharacter     peek                (void) override;

        /// Ignores the next byte
        virtual void            ignore                (void) override;


        /// Checks for end of file
        /// \return End of file
        virtual bool       is_eof                (void) override;


        /// Reads a chunk of raw binary data
        /// \param buffer raw buffer
        /// \param size size of raw buffer
        /// \return actual number of bytes read
        virtual DTsize          read                (uint8_t *buffer, DTsize size) override;

        /// Writes a chunk of raw binary data
        /// \param buffer raw buffer
        /// \param size size of raw buffer
        virtual void            write                (const uint8_t *buffer, DTsize size) override;

    private:
        DTsize                _length;
        int32_t               _file;
        bool           _eof;
};

//==============================================================================
//==============================================================================


} // DT3

#endif
