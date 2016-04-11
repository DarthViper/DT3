//==============================================================================
///
///    File: TextFileStream.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/FileBuffer/TextFileStream.hpp"
#include "DT3Core/Types/FileBuffer/FileHandle.hpp"
#include "DT3Core/Types/Utility/MoreStrings.hpp"
#include "DT3Core/Types/Utility/Assert.hpp"
#include "DT3Core/Types/Utility/Progress.hpp"
#include <sstream>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

TextFileStream::TextFileStream (void)
        :    _start            (0),
                _length            (0),
                _last_update    (0),
        _eof            (false),
        _ignore_whitespace  (false)
{

}

TextFileStream::~TextFileStream (void)
{

}

//==============================================================================
//==============================================================================

const std::shared_ptr<FileHandle>& TextFileStream::file_handle (void) const
{
        return _file;
}

void TextFileStream::set_file_handle (const std::shared_ptr<FileHandle> &file_handle)
{
        _file = file_handle;
}

//==============================================================================
//==============================================================================

void TextFileStream::eat_whitespace    (void)
{
        if (_eof)
                return;

        DTcharacter c = peek();

#if DT3_COMPILER == DT3_VISUALC || DT3_OS == DT3_ANDROID
        while (!isgraph(c) && _file->g() < (_start + _length)) {
#else
    while (!std::isgraph(c) && _file->g() < (_start + _length)) {
#endif
                ignore();
                c = peek();
        }
}

void TextFileStream::read_float_string (DTcharacter buffer[TEMP_BUFFER_SIZE])
{
        eat_whitespace();

    DTsize file_g = _file->g();
        _eof = (file_g == -1) || (file_g >= (_start + _length));
        if (_eof)
                return;

        DTcharacter c = peek();
        uint16_t i = 0;

        while (    i < TEMP_BUFFER_SIZE &&
                        (c == '+' || c == '-' || (c >= '0' && c <= '9') || c == '.' || c == 'e' || c == 'E')  &&
                        _file->g() < (_start + _length)) {
                _file->read((uint8_t*) &buffer[i++], 1);
                c = peek();
        }
        buffer[i++] = '\0';

    update_progress();
}

//==============================================================================
//==============================================================================

Stream& TextFileStream::operator<< (const bool n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const int8_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const int16_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const int32_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const uint8_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const uint16_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const uint32_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const int64_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const uint64_t n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

#if DT3_SIZES_ARE_DISTINCT_TYPES
Stream& TextFileStream::operator<< (const DTsize n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}
#endif

Stream& TextFileStream::operator<< (const DTfloat n)
{
        std::stringstream ss;
    ss.precision(7);
    ss.setf(std::ios::showpoint);
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const DTdouble n)
{
        std::stringstream ss;
    ss.precision(17);
    ss.setf(std::ios::showpoint);
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const DTlonglong n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const DTcharacter n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const char* n)
{
        std::stringstream ss;
        ss << n;
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

Stream& TextFileStream::operator<< (const std::string &n)
{
        std::stringstream ss;
        ss << n.c_str();
        _file->write((const uint8_t*) ss.str().c_str(), ss.str().size());
        return *this;
}

//==============================================================================
//==============================================================================

Stream& TextFileStream::operator>> (bool &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<bool>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (int8_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<int8_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (int16_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<int16_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (int32_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<int32_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (uint8_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<uint8_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (uint16_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<uint16_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (uint32_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<uint32_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (int64_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<int64_t>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (uint64_t &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<uint64_t>(buffer);
        return *this;
}

#if DT3_SIZES_ARE_DISTINCT_TYPES
Stream& TextFileStream::operator>> (DTsize &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<DTsize>(buffer);
        return *this;
}
#endif

Stream& TextFileStream::operator>> (DTfloat &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<DTfloat>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (DTdouble &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<DTdouble>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (DTlonglong &n)
{
        DTcharacter buffer[TEMP_BUFFER_SIZE];
        read_float_string (buffer);
        n = MoreStrings::cast_from_string<DTlonglong>(buffer);
        return *this;
}

Stream& TextFileStream::operator>> (DTcharacter &n)
{
    DTsize file_g = _file->g();
        _eof = (file_g == -1) || (file_g >= (_start + _length));
        _file->read((uint8_t*) &n, 1);

    update_progress();

        return *this;
}

Stream& TextFileStream::operator>> (std::string &n)
{
    if (_ignore_whitespace) {
        eat_whitespace();

        DTsize file_g = _file->g();
        _eof = (file_g == -1) || (file_g >= (_start + _length));
        if (_eof)
            return *this;

        DTcharacter buffer[TEMP_BUFFER_SIZE];
        DTcharacter c = peek();
        uint16_t i = 0;

        while (i < TEMP_BUFFER_SIZE-1 && c != '\n') {
            _file->read((uint8_t*) &buffer[i++], 1);
            c = peek();
        }
        buffer[i++] = '\0';

        n = buffer;

        update_progress();

        return *this;

    } else {

        eat_whitespace();

        DTsize file_g = _file->g();
        _eof = (file_g == -1) || (file_g >= (_start + _length));
        if (_eof)
            return *this;

        DTcharacter buffer[TEMP_BUFFER_SIZE];
        DTcharacter c = peek();
        uint16_t i = 0;

#if DT3_COMPILER == DT3_VISUALC || DT3_OS == DT3_ANDROID
        while (i < TEMP_BUFFER_SIZE-1 && !isspace(c) ) {
#else
        while (i < TEMP_BUFFER_SIZE-1 && !std::isspace(c) ) {
#endif
            _file->read((uint8_t*) &buffer[i++], 1);
            c = peek();
        }
        buffer[i++] = '\0';

        n = buffer;

        update_progress();

        return *this;
    }
}

//==============================================================================
//==============================================================================

DTsize TextFileStream::p (void)
{
        return _file->p() - _start;
}

DTsize TextFileStream::g (void)
{
        return _file->g() - _start;
}

void TextFileStream::seek_p (DToffset p, Relative r)
{
        switch (r) {
                case FROM_BEGINNING:    _file->seek_p(_start+p, FileHandle::FROM_BEGINNING);            break;
                case FROM_CURRENT:        _file->seek_p(p, FileHandle::FROM_CURRENT);                        break;
                case FROM_END:            _file->seek_p(_start+_length-p, FileHandle::FROM_BEGINNING);    break;
        };
}

void TextFileStream::seek_g (DToffset g, Relative r)
{
        switch (r) {
                case FROM_BEGINNING:    _file->seek_g(_start+g, FileHandle::FROM_BEGINNING);            break;
                case FROM_CURRENT:        _file->seek_g(g, FileHandle::FROM_CURRENT);                        break;
                case FROM_END:            _file->seek_g(_start+_length-g, FileHandle::FROM_BEGINNING);    break;
        };
}

DTcharacter TextFileStream::peek (void)
{
        DTcharacter c = _file->peek();
        return c;
}

void TextFileStream::ignore (void)
{
    DTsize file_g = _file->g();
        _eof = (file_g == -1) || (file_g >= (_start + _length));
        _file->ignore();
}

bool TextFileStream::is_eof (void)
{
        return _eof;
}

void TextFileStream::line (DTcharacter *buffer, uint32_t size)
{
    DTsize file_g = _file->g();
        _eof = (file_g == -1) || (file_g >= (_start + _length));
        if (_eof)
                return;

        DTcharacter c = peek();
        uint32_t i = 0;

        while (i < (size-1) && _file->g() < (_start + _length) && (c != '\n' && c != '\r' && c != -1) ) {

                // read the character
                _file->read((uint8_t*) &buffer[i++], 1);

                c = peek();
        }

        // ignore following newline characters
        while (_file->g() < (_start + _length) && (c == '\n' || c == '\r') && (c != -1) ) {
                ignore();
                c = peek();
        }

        buffer[i] = '\0';

        ASSERT(!_eof);

    update_progress();
}

//==============================================================================
//==============================================================================

void TextFileStream::open_file_fragment    (const std::shared_ptr<FileHandle> &file, DTsize start, DTsize length, std::shared_ptr<Progress> progress)
{
        set_file_handle(file);

        _start = start;
        _length = length;

    _file->seek_g(_start, FileHandle::FROM_BEGINNING);

    _progress = progress;
}

//==============================================================================
//==============================================================================

void TextFileStream::close (void)
{
        _file.reset();
}

//==============================================================================
//==============================================================================

void TextFileStream::update_progress (void)
{
        // Update Progress
        if (_progress) {
                _progress->update(_file->g(), _length);
                _last_update = 0;
        }
}

//==============================================================================
//==============================================================================

} // DT3
