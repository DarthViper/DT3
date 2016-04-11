#pragma once
#ifndef DT3_TEXTFILESTREAM
#define DT3_TEXTFILESTREAM
//==============================================================================
///
///    File: TextFileStream.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/FileBuffer/TextStream.hpp"
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

class TextFileStream: public TextStream {
    public:
        DEFINE_TYPE(TextFileStream,TextStream)
        DEFINE_CREATE

                                            TextFileStream          (void);
        explicit                            TextFileStream          (const FilePath &pathname);

    private:
                                            TextFileStream          (const TextFileStream &rhs);
        TextFileStream &                    operator =              (const TextFileStream &rhs);

    public:
        virtual                             ~TextFileStream         (void);

        public:
                Stream&                             operator<<              (const Stream::FS) override {    *this << " ";    return *this;    }
                Stream&                             operator<<              (const bool n) override;
                Stream&                             operator<<              (const int8_t n) override;
                Stream&                             operator<<              (const int16_t n) override;
                Stream&                             operator<<              (const int32_t n) override;
                Stream&                             operator<<              (const uint8_t n) override;
                Stream&                             operator<<              (const uint16_t n) override;
                Stream&                             operator<<              (const uint32_t n) override;
                Stream&                             operator<<              (const int64_t n) override;
                Stream&                             operator<<              (const uint64_t n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                             operator<<              (const DTsize n) override;
#endif
                Stream&                             operator<<              (const DTfloat n) override;
                Stream&                             operator<<              (const DTdouble n) override;
                Stream&                             operator<<              (const DTlonglong n) override;
                Stream&                             operator<<              (const DTcharacter n) override;
                Stream&                             operator<<              (const char* n) override;
                Stream&                             operator<<              (const std::string &n) override;
                Stream&                             operator<<              (const Stream& n);


                Stream&                             operator>>              (bool &n) override;
                Stream&                             operator>>              (int8_t &n) override;
                Stream&                             operator>>              (int16_t &n) override;
                Stream&                             operator>>              (int32_t &n) override;
                Stream&                             operator>>              (uint8_t &n) override;
                Stream&                             operator>>              (uint16_t &n) override;
                Stream&                             operator>>              (uint32_t &n) override;
                Stream&                             operator>>              (int64_t &n) override;
                Stream&                             operator>>              (uint64_t &n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                             operator>>              (DTsize &n) override;
#endif
                Stream&                             operator>>              (DTfloat &n) override;
                Stream&                             operator>>              (DTdouble &n) override;
                Stream&                             operator>>              (DTlonglong &n) override;
                Stream&                             operator>>              (DTcharacter &n) override;
                Stream&                             operator>>              (std::string &n) override;


                /// Return write position
                /// \return write position
                DTsize                              p                       (void) override;

                /// Return read position
                /// \return read position
                DTsize                              g                       (void) override;

                /// Change write position
                /// \param p position
                /// \param r relative
                void                                seek_p                  (DToffset p, Relative r) override;

                /// Change read position
                /// \param p position
                /// \param r relative
                void                                seek_g                  (DToffset g, Relative r) override;


                /// Peeks ahead at the next byte
                /// \return next byte
                DTcharacter                         peek                    (void);

                /// Ignores the next byte
                void                                ignore                  (void);


                /// Checks for end of file
                /// \return End of file
                bool                           is_eof                  (void);

                /// Clears end of file flag
                void                                clear_EOF               (void)  {   _eof = false;   }

                /// Reads a line into a buffer
                /// \param buffer raw buffer
                /// \param size raw buffer length
                void                                line                    (DTcharacter *buffer, uint32_t size);

                /// Associate the file handle with the stream. This opens a fragment of a file.
                /// \param file file handle
                /// \param start start of the fragment
                /// \param length length of the fragment
                /// \param progress progress
                void                                open_file_fragment      (const std::shared_ptr<FileHandle> &file, DTsize start, DTsize length, std::shared_ptr<Progress> progress = NULL);

                /// Close the stream
                void                                close                   (void);

                /// Length of the stream
                /// \return Length of the stream
                DTsize                              length                  (void) const            {    return _length;        }

                /// Returns the start of the stream if opening a fragment
                /// \return Start position
                DTsize                              start                   (void) const            {    return _start;        }

                /// Returns the file handle associated with the stream
                /// \return file handle
                const std::shared_ptr<FileHandle>&  file_handle             (void) const;

                /// Sets the file handle associated with the stream
                /// \param file_handle File handle
                void                                set_file_handle         (const std::shared_ptr<FileHandle> &file_handle);

                /// Sets the ignore whitespace flag. This ignores spaces when reading strings
                /// \param ignore_whitepace ignore whitepace flag
        void                                set_ignore_whitespace   (bool ignore_whitepace)    {   _ignore_whitespace = ignore_whitepace;  }

        private:
        void                                update_progress         (void);

                std::shared_ptr<FileHandle>         _file;
        bool                           _ignore_whitespace;

                DTsize                              _start;
                DTsize                              _length;
                DTsize                              _last_update;

                std::shared_ptr<Progress>           _progress;

        bool                           _eof;

        static const DTsize TEMP_BUFFER_SIZE = 1024;

                void                                eat_whitespace            (void);
                void                                read_float_string       (DTcharacter buffer[TEMP_BUFFER_SIZE]);
};

//==============================================================================
//==============================================================================


} // DT3

#endif
