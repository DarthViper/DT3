#pragma once
#ifndef DT3_TEXTBUFFERSTREAM
#define DT3_TEXTBUFFERSTREAM
//==============================================================================
///
///    File: TextBufferStream.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/FileBuffer/TextStream.hpp"
#include <string>
#include <sstream>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class Stream;

//==============================================================================
/// Class
//==============================================================================

class TextBufferStream: public TextStream {
    public:
        DEFINE_TYPE(TextBufferStream,TextStream)
        DEFINE_CREATE

                                TextBufferStream        (void);
        explicit                TextBufferStream        (const std::string &s)  {    set_buffer(s);    }
        explicit                TextBufferStream        (const DTcharacter *s)    {    set_buffer(s);    }
        private:
                                TextBufferStream        (const TextBufferStream &rhs);
        TextBufferStream &        operator =                (const TextBufferStream &rhs);
        public:
        virtual                    ~TextBufferStream        (void);

        public:

                Stream&                operator<<          (const Stream::FS) override     {    *this << " ";    return *this;    }
                Stream&                operator<<            (const bool n) override;
                Stream&                operator<<            (const int8_t n) override;
                Stream&                operator<<            (const int16_t n) override;
                Stream&                operator<<            (const int32_t n) override;
                Stream&                operator<<            (const uint8_t n) override;
                Stream&                operator<<            (const uint16_t n) override;
                Stream&                operator<<            (const uint32_t n) override;
                Stream&                operator<<            (const int64_t n) override;
                Stream&                operator<<            (const uint64_t n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                operator<<            (const DTsize n) override;
#endif
                Stream&                operator<<            (const DTfloat n) override;
                Stream&                operator<<            (const DTdouble n) override;
                Stream&                operator<<            (const DTlonglong n) override;
                Stream&                operator<<            (const DTcharacter n) override;
                Stream&                operator<<            (const char* n) override;
                Stream&                operator<<            (const std::string &n) override;
                Stream&                operator<<            (const TextBufferStream& n);


                Stream&                operator>>            (bool &n) override;
                Stream&                operator>>            (int8_t &n) override;
                Stream&                operator>>            (int16_t &n) override;
                Stream&                operator>>            (int32_t &n) override;
                Stream&                operator>>            (uint8_t &n) override;
                Stream&                operator>>            (uint16_t &n) override;
                Stream&                operator>>            (uint32_t &n) override;
                Stream&                operator>>            (int64_t &n) override;
                Stream&                operator>>            (uint64_t &n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                operator>>            (DTsize &n) override;
#endif
                Stream&                operator>>            (DTfloat &n) override;
                Stream&                operator>>            (DTdouble &n) override;
                Stream&                operator>>            (DTlonglong &n) override;
                Stream&                operator>>            (DTcharacter &n) override;
                Stream&                operator>>            (std::string &n) override;


                /// Return write position
                /// \return write position
                DTsize                          p                   (void) override;

                /// Return read position
                /// \return read position
                DTsize                          g                   (void) override;

                /// Change write position
                /// \param p position
                /// \param r relative
                void                            seek_p              (DToffset p, Relative r) override;

                /// Change read position
                /// \param p position
                /// \param r relative
                void                            seek_g              (DToffset g, Relative r) override;


                /// Peeks ahead at the next byte
                /// \return next byte
        DTcharacter                     peek                (void);

                /// Ignores the next byte
        void                            ignore              (void);

                /// Reads a line into a buffer
                /// \param buffer raw buffer
                /// \param size raw buffer length
        void                            line                (DTcharacter *buffer, DTsize size);

                /// Returns the buffer
                /// \return buffer
                std::string                        buffer              (void)                              {    return std::string(_buffer.str());        }

                /// Sets the buffer contents
                /// \param buffer new buffer contents
                void                            set_buffer            (std::string buffer);

                /// Sets the ignore whitespace flag. This ignores spaces when reading strings
                /// \param ignore_whitepace ignore whitepace flag
        void                            set_ignore_whitespace   (bool ignore_whitepace)    {   _ignore_whitespace = ignore_whitepace;  }

        private:
                std::stringstream   _buffer;
        bool                       _ignore_whitespace;

};

//==============================================================================
//==============================================================================


} // DT3

#endif
