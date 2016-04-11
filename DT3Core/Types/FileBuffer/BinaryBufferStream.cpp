//==============================================================================
///
///    File: BinaryBufferStream.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/FileBuffer/BinaryBufferStream.hpp"
#include "DT3Core/Types/Utility/Endian.hpp"
#include <string>
#include <cstring>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

BinaryBufferStream::BinaryBufferStream (void)
        :    _logical_size    (0),
                _pos_p            (0),
                _pos_g            (0)
{

}

BinaryBufferStream::~BinaryBufferStream (void)
{

}

//==============================================================================
//==============================================================================

Stream& BinaryBufferStream::operator<< (const bool n)
{
        return operator << ((int8_t) n);
}

Stream& BinaryBufferStream::operator<< (const int8_t nc)
{
        int8_t n = nc;
        grow (sizeof(int8_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<int8_t*>(&_stream[_pos_p])) = (int8_t) n;
        _pos_p += sizeof(int8_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const int16_t nc)
{
        int16_t n = nc;
        grow (sizeof(int16_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<int16_t*>(&_stream[_pos_p])) = (int16_t) n;
        _pos_p += sizeof(int16_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const int32_t nc)
{
        int32_t n = nc;
        grow (sizeof(int32_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<int32_t*>(&_stream[_pos_p])) = (int32_t) n;
        _pos_p += sizeof(int32_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const uint8_t nc)
{
        uint8_t n = nc;
        grow (sizeof(uint8_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<uint8_t*>(&_stream[_pos_p])) = (uint8_t) n;
        _pos_p += sizeof(uint8_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const uint16_t nc)
{
        uint16_t n = nc;
        grow (sizeof(uint16_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<uint16_t*>(&_stream[_pos_p])) = (uint16_t) n;
        _pos_p += sizeof(uint16_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const uint32_t nc)
{
        uint32_t n = nc;
        grow (sizeof(uint32_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<uint32_t*>(&_stream[_pos_p])) = (uint32_t) n;
        _pos_p += sizeof(uint32_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const int64_t nc)
{
        int64_t n = nc;
        grow (sizeof(uint64_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<uint64_t*>(&_stream[_pos_p])) = (uint64_t) n;
        _pos_p += sizeof(uint64_t);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const uint64_t nc)
{
        uint64_t n = nc;
        grow (sizeof(uint64_t));
        Endian::to_little_endian(n);
        *(reinterpret_cast<uint64_t*>(&_stream[_pos_p])) = (uint64_t) n;
        _pos_p += sizeof(uint64_t);

        return *this;
}

#if DT3_SIZES_ARE_DISTINCT_TYPES
Stream& BinaryBufferStream::operator<< (const DTsize nc)
{
        DTsize n = nc;
        grow (sizeof(DTsize));
        Endian::to_little_endian(n);
        *(reinterpret_cast<DTsize*>(&_stream[_pos_p])) = (DTsize) n;
        _pos_p += sizeof(DTsize);

        return *this;
}
#endif

Stream& BinaryBufferStream::operator<< (const DTfloat nc)
{
        DTfloat n = nc;
        grow (sizeof(DTfloat));
        Endian::to_little_endian(n);

    DTfloat *mem = reinterpret_cast<DTfloat*>(&_stream[_pos_p]);
    ::memcpy(mem, &n, sizeof(DTfloat));

        _pos_p += sizeof(DTfloat);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const DTdouble nc)
{
        DTdouble n = nc;
        grow (sizeof(DTdouble));
        Endian::to_little_endian(n);

        DTdouble *mem = reinterpret_cast<DTdouble*>(&_stream[_pos_p]);
    ::memcpy(mem, &n, sizeof(DTdouble));

        _pos_p += sizeof(DTdouble);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const DTlonglong nc)
{
        DTlonglong n = nc;
        grow (sizeof(DTlonglong));
        Endian::to_little_endian(n);

        DTlonglong *mem = reinterpret_cast<DTlonglong*>(&_stream[_pos_p]);
    ::memcpy(mem, &n, sizeof(DTlonglong));

        _pos_p += sizeof(DTlonglong);

        return *this;
}

Stream& BinaryBufferStream::operator<< (const DTcharacter n)
{
        return operator << ((uint8_t) n);
}

Stream& BinaryBufferStream::operator<< (const char* n)
{
        std::string n_str(n);

        return operator << (n_str);
}

Stream& BinaryBufferStream::operator<< (const std::string &n)
{
        for (uint32_t i = 0; i < n.size(); ++i)
                operator << ((DTcharacter) n[i]);

        operator << ('\0');

        return *this;
}

Stream& BinaryBufferStream::operator<< (const BinaryBufferStream& n)
{
        for (uint32_t i = 0; i < n._logical_size; ++i)
                operator << (n._stream[i]);

        return *this;
}

//==============================================================================
//==============================================================================

Stream& BinaryBufferStream::operator>> (bool &n)
{
        n = *(reinterpret_cast<int8_t*>(&_stream[_pos_g])) != (int8_t)0;
        Endian::from_little_endian(n);
        _pos_g += sizeof(int8_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (int8_t &n)
{
        n = *(reinterpret_cast<int8_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(int8_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (int16_t &n)
{
        n = *(reinterpret_cast<int16_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(int16_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (int32_t &n)
{
        n = *(reinterpret_cast<int32_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(int32_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (uint8_t &n)
{
        n = *(reinterpret_cast<uint8_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(uint8_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (uint16_t &n)
{
        n = *(reinterpret_cast<uint16_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(uint16_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (uint32_t &n)
{
        n = *(reinterpret_cast<uint32_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(uint32_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (int64_t &n)
{
        n = *(reinterpret_cast<uint64_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(uint64_t);

        return *this;
}

Stream& BinaryBufferStream::operator>> (uint64_t &n)
{
        n = *(reinterpret_cast<uint64_t*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(uint64_t);

        return *this;
}

#if DT3_SIZES_ARE_DISTINCT_TYPES
Stream& BinaryBufferStream::operator>> (DTsize &n)
{
        n = *(reinterpret_cast<DTsize*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(DTsize);

        return *this;
}
#endif

Stream& BinaryBufferStream::operator>> (DTfloat &n)
{
    DTfloat *mem = reinterpret_cast<DTfloat*>(&_stream[_pos_g]);
    ::memcpy(&n, mem, sizeof(DTfloat));

        Endian::from_little_endian(n);
        _pos_g += sizeof(DTfloat);

        return *this;
}

Stream& BinaryBufferStream::operator>> (DTdouble &n)
{
    DTdouble *mem = reinterpret_cast<DTdouble*>(&_stream[_pos_g]);
    ::memcpy(&n, mem, sizeof(DTdouble));

        Endian::from_little_endian(n);
        _pos_g += sizeof(DTdouble);

        return *this;
}

Stream& BinaryBufferStream::operator>> (DTlonglong &n)
{
    DTlonglong *mem = reinterpret_cast<DTlonglong*>(&_stream[_pos_g]);
    ::memcpy(&n, mem, sizeof(DTlonglong));

        Endian::from_little_endian(n);
        _pos_g += sizeof(DTlonglong);

        return *this;
}

Stream& BinaryBufferStream::operator>> (DTcharacter &n)
{
        n = *(reinterpret_cast<DTcharacter*>(&_stream[_pos_g]));
        Endian::from_little_endian(n);
        _pos_g += sizeof(DTcharacter);

        return *this;
}

Stream& BinaryBufferStream::operator>> (std::string &n)
{
        n.clear();

        DTcharacter c = *(reinterpret_cast<DTcharacter*>(&_stream[_pos_g]));
        _pos_g += sizeof(DTcharacter);

        while (c != '\0') {
                n += c;

                c = *(reinterpret_cast<DTcharacter*>(&_stream[_pos_g]));
                _pos_g += sizeof(DTcharacter);
        }

        return *this;
}

//==============================================================================
//==============================================================================

void BinaryBufferStream::resize (const DTsize size)
{
        const uint32_t BUFFER_SIZE = 2048;

        std::size_t allocate_size = ((size/BUFFER_SIZE) + 1) * BUFFER_SIZE;
        if (allocate_size > _stream.size()) {
                _stream.resize(allocate_size);
        }
        _logical_size = size;
}

void BinaryBufferStream::grow (DTsize size)
{
        if (_logical_size < (uint32_t) (_pos_p + size)) {
                resize(_pos_p+size);
        }
}

//==============================================================================
//==============================================================================

DTsize BinaryBufferStream::p (void)
{
        return _pos_p;
}

DTsize BinaryBufferStream::g (void)
{
        return _pos_g;
}

void BinaryBufferStream::seek_p (DToffset p, BinaryBufferStream::Relative r)
{
        switch (r) {
                case FROM_BEGINNING:
                        _pos_p = p;
                        break;
                case FROM_END:
                        _pos_p = (DTsize) _logical_size - p;
                        break;
                case FROM_CURRENT:
                        _pos_p += p;
                        break;
        };
}

void BinaryBufferStream::seek_g (DToffset g, BinaryBufferStream::Relative r)
{
        switch (r) {
                case FROM_BEGINNING:
                        _pos_g = g;
                        break;
                case FROM_END:
                        _pos_g = (DTsize) _logical_size - g;
                        break;
                case FROM_CURRENT:
                        _pos_g += g;
                        break;
        };
}

//==============================================================================
//==============================================================================

void BinaryBufferStream::set_buffer (void *b, DTsize size)
{
        // Build and copy data into buffer
        resize(size);
        memcpy(&_stream[0], b, (size_t) size);
}

//==============================================================================
//==============================================================================


} // DT3
