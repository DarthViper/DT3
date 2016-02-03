#pragma once
#ifndef DT3_TEXTBUFFERSTREAM
#define DT3_TEXTBUFFERSTREAM
//==============================================================================
///
///	File: TextBufferStream.hpp
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

                                TextBufferStream		(void);
        explicit                TextBufferStream		(const std::string &s)  {	set_buffer(s);	}
        explicit                TextBufferStream		(const DTcharacter *s)	{	set_buffer(s);	}
        private:
                                TextBufferStream		(const TextBufferStream &rhs);
        TextBufferStream &		operator =				(const TextBufferStream &rhs);
        public:
        virtual					~TextBufferStream		(void);

        public:

                Stream&				operator<<			(const Stream::FS)	{	*this << " ";	return *this;	}
                Stream&				operator<<			(const bool n);
                Stream&				operator<<			(const int8_t n);
                Stream&				operator<<			(const int16_t n);
                Stream&				operator<<			(const int32_t n);
                Stream&				operator<<			(const uint8_t n);
                Stream&				operator<<			(const uint16_t n);
                Stream&				operator<<			(const uint32_t n);
                Stream&				operator<<			(const int64_t n);
                Stream&				operator<<			(const uint64_t n);
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&				operator<<			(const DTsize n);
#endif
                Stream&				operator<<			(const DTfloat n);
                Stream&				operator<<			(const DTdouble n);
                Stream&				operator<<			(const DTlonglong n);
                Stream&				operator<<			(const DTcharacter n);
                Stream&				operator<<			(const char* n);
                Stream&				operator<<			(const std::string &n);
                Stream&				operator<<			(const TextBufferStream& n);


                Stream&				operator>>			(bool &n);
                Stream&				operator>>			(int8_t &n);
                Stream&				operator>>			(int16_t &n);
                Stream&				operator>>			(int32_t &n);
                Stream&				operator>>			(uint8_t &n);
                Stream&				operator>>			(uint16_t &n);
                Stream&				operator>>			(uint32_t &n);
                Stream&				operator>>			(int64_t &n);
                Stream&				operator>>			(uint64_t &n);
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&				operator>>			(DTsize &n);
#endif
                Stream&				operator>>			(DTfloat &n);
                Stream&				operator>>			(DTdouble &n);
                Stream&				operator>>			(DTlonglong &n);
                Stream&				operator>>			(DTcharacter &n);
                Stream&				operator>>			(std::string &n);


                /// Return write position
                /// \return write position
                DTsize                          p                   (void);

                /// Return read position
                /// \return read position
                DTsize                          g                   (void);

                /// Change write position
                /// \param p position
                /// \param r relative
                void                            seek_p              (DToffset p, Relative r);

                /// Change read position
                /// \param p position
                /// \param r relative
                void                            seek_g              (DToffset g, Relative r);


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
                std::string						buffer              (void)                              {	return std::string(_buffer.str());		}

                /// Sets the buffer contents
                /// \param buffer new buffer contents
                void							set_buffer			(std::string buffer);

                /// Sets the ignore whitespace flag. This ignores spaces when reading strings
                /// \param ignore_whitepace ignore whitepace flag
        void                            set_ignore_whitespace   (bool ignore_whitepace)    {   _ignore_whitespace = ignore_whitepace;  }

        private:
                std::stringstream				_buffer;
        bool                       _ignore_whitespace;

};

//==============================================================================
//==============================================================================


} // DT3

#endif
