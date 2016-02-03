//==============================================================================
///
///	File: TextBufferStream.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/FileBuffer/TextBufferStream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

TextBufferStream::TextBufferStream (void)
    :   _ignore_whitespace  (true)
{

}

TextBufferStream::~TextBufferStream (void)
{

}

//==============================================================================
//==============================================================================

Stream& TextBufferStream::operator<< (const bool n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const int8_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const int16_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const int32_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const uint8_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const uint16_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const uint32_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const int64_t n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const uint64_t n)
{
        _buffer << n;
        return *this;
}

#if DT3_SIZES_ARE_DISTINCT_TYPES
Stream& TextBufferStream::operator<< (const DTsize n)
{
        _buffer << n;
        return *this;
}
#endif

Stream& TextBufferStream::operator<< (const DTfloat n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const DTdouble n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const DTlonglong n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const DTcharacter n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const char* n)
{
        _buffer << n;
        return *this;
}

Stream& TextBufferStream::operator<< (const std::string &n)
{
        _buffer << n.c_str();
        return *this;
}

Stream& TextBufferStream::operator<< (const TextBufferStream& n)
{
        for (uint32_t i = 0; i < n._buffer.str().size(); ++i)
                operator << (n._buffer.str()[i]);

        return *this;
}


//==============================================================================
//==============================================================================

Stream& TextBufferStream::operator>> (bool &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (int8_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (int16_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (int32_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (uint8_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (uint16_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (uint32_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (int64_t &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (uint64_t &n)
{
        _buffer >> n;
        return *this;
}

#if DT3_SIZES_ARE_DISTINCT_TYPES
Stream& TextBufferStream::operator>> (DTsize &n)
{
        _buffer >> n;
        return *this;
}
#endif

Stream& TextBufferStream::operator>> (DTfloat &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (DTdouble &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (DTlonglong &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (DTcharacter &n)
{
        _buffer >> n;
        return *this;
}

Stream& TextBufferStream::operator>> (std::string &n)
{
    if (_ignore_whitespace) {

        // To EOF like normal
        n.clear();
        DTcharacter c = 0;
        _buffer >> std::noskipws >> c;

        while (!_buffer.eof()) {
            n += c;
            _buffer >> std::noskipws >> c;
        }

        return *this;

    } else {

        // To whitespace (like a standard stream)
        n.clear();

        DTcharacter c = peek();

        // Eat whitespace
#if DT3_OS == DT3_WINDOWS
        while (isspace(c) && !_buffer.eof()) {
#else
        while (std::isspace(c) && !_buffer.eof()) {
#endif
            _buffer >> std::noskipws >> c;

            c = peek();
        }

        // Fill std::string
#if DT3_OS == DT3_WINDOWS
        while (!isspace(c) && !_buffer.eof()) {
#else
        while (!std::isspace(c) && !_buffer.eof()) {
#endif
            _buffer >> std::noskipws >> c;
            n += c;

            c = peek();
        }

        return *this;
    }
}

//==============================================================================
//==============================================================================

DTsize TextBufferStream::p (void)
{
        return (int32_t) _buffer.tellp();
}

DTsize TextBufferStream::g (void)
{
        return (int32_t) _buffer.tellg();
}

void TextBufferStream::seek_p (DToffset p, Relative r)
{
        switch (r) {
                case FROM_BEGINNING:	_buffer.seekp(p,std::ios::beg);	break;
                case FROM_CURRENT:		_buffer.seekp(p,std::ios::cur);	break;
                case FROM_END:			_buffer.seekp(p,std::ios::end);	break;
        };
}

void TextBufferStream::seek_g (DToffset g, Relative r)
{
        switch (r) {
                case FROM_BEGINNING:	_buffer.seekg(g,std::ios::beg);	break;
                case FROM_CURRENT:		_buffer.seekg(g,std::ios::cur);	break;
                case FROM_END:			_buffer.seekg(g,std::ios::end);	break;
        };
}

//==============================================================================
//==============================================================================

DTcharacter TextBufferStream::peek (void)
{
    return static_cast<DTcharacter>(_buffer.peek());
}

void TextBufferStream::ignore (void)
{
    _buffer.ignore();
}

void TextBufferStream::line (DTcharacter *buffer, DTsize size)
{
    _buffer.getline(buffer, (size_t) size);
}

//==============================================================================
//==============================================================================

void TextBufferStream::set_buffer (std::string buffer)
{
        _buffer.clear();
        _buffer << buffer.c_str();
}

//==============================================================================
//==============================================================================


} // DT3
