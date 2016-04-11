#pragma once
#ifndef DT3_FILEHANDLEUNCOMPRESSED
#define DT3_FILEHANDLEUNCOMPRESSED
//==============================================================================
///
///    File: FileHandleUncompressed.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/FileBuffer/FileHandle.hpp"
#include <fstream>

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

class FileHandleUncompressed: public FileHandle {
    public:
        DEFINE_TYPE(FileHandleUncompressed,FileHandle)
        //DEFINE_CREATE_AND_CLONE
        DEFINE_CREATE

                                    FileHandleUncompressed      (void);
    private:
                                    FileHandleUncompressed      (const FileHandleUncompressed &rhs);
        FileHandleUncompressed &    operator =                  (const FileHandleUncompressed &rhs);
    public:
        virtual                     ~FileHandleUncompressed     (void);

    public:
        //
        // File access routines
        //

        /// Opens a file
        /// \param pathname path to file
        /// \param read read or write
        /// \return Error
        virtual DTerr           open_file            (const FilePath &pathname, bool read = true);

        /// Close the file handle
        virtual void            close                (void) override;

        /// Returns the length of the file
        /// \return Length of the file
        virtual DTsize          length              (void) const override    {    return _length;            }


        /// Return write position
        /// \return write position
        virtual DTsize          p                   (void) override  {    return (DTsize) _file.tellp();    }

        /// Return read position
        /// \return read position
        virtual DTsize          g                   (void)  override   {    return (DTsize) _file.tellg();    }

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
        virtual DTcharacter     peek                (void)  override   {    return static_cast<DTcharacter>(_file.peek());    }

        /// Ignores the next byte
        virtual void            ignore                (void)  override  {    uint8_t b; read(&b, 1);    }


        /// Checks for end of file
        /// \return End of file
        virtual bool       is_eof                (void) override    {    return _file.eof();        }


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
        std::fstream        _file;
};

//==============================================================================
//==============================================================================


} // DT3

#endif
