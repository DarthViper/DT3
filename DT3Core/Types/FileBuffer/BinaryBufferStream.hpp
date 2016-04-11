#pragma once
//==============================================================================
///
///    File: BinaryBufferStream.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/FileBuffer/BinaryStream.hpp"
#include <vector>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Class
//==============================================================================

class BinaryBufferStream: public BinaryStream {
    public:
        DEFINE_TYPE(BinaryBufferStream,BinaryStream)
                DEFINE_CREATE

                                    BinaryBufferStream        (void);
        private:
                                    BinaryBufferStream        (const BinaryBufferStream &rhs);
        BinaryBufferStream &        operator =                (const BinaryBufferStream &rhs);
        public:
        virtual                        ~BinaryBufferStream        (void);

        public:

                Stream&                     operator<<              (const Stream::FS)    {    return *this;    }
                Stream&                     operator<<              (const bool n);
                Stream&                     operator<<              (const int8_t n);
                Stream&                     operator<<              (const int16_t n);
                Stream&                     operator<<              (const int32_t n);
                Stream&                     operator<<              (const uint8_t n);
                Stream&                     operator<<              (const uint16_t n);
                Stream&                     operator<<              (const uint32_t n);
                Stream&                     operator<<              (const int64_t n);
                Stream&                     operator<<              (const uint64_t n);
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                     operator<<              (const DTsize n);
#endif
                Stream&                     operator<<              (const DTfloat n);
                Stream&                     operator<<              (const DTdouble n);
                Stream&                     operator<<              (const DTlonglong n);
                Stream&                     operator<<              (const DTcharacter n);
                Stream&                     operator<<              (const char* n);
                Stream&                     operator<<              (const std::string &n);
                Stream&                     operator<<              (const BinaryBufferStream& n);


                Stream&                     operator>>              (bool &n);
                Stream&                     operator>>              (int8_t &n);
                Stream&                     operator>>              (int16_t &n);
                Stream&                     operator>>              (int32_t &n);
                Stream&                     operator>>              (uint8_t &n);
                Stream&                     operator>>              (uint16_t &n);
                Stream&                     operator>>              (uint32_t &n);
                Stream&                     operator>>              (int64_t &n);
                Stream&                     operator>>              (uint64_t &n);
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                     operator>>              (DTsize &n);
#endif
                Stream&                     operator>>              (DTfloat &n);
                Stream&                     operator>>              (DTdouble &n);
                Stream&                     operator>>              (DTlonglong &n);
                Stream&                     operator>>              (DTcharacter &n);
                Stream&                     operator>>              (std::string &n);


                /// Return write position
                /// \return write position
                DTsize                        p                       (void);

                /// Return read position
                /// \return read position
                DTsize                        g                       (void);

                /// Change write position
                /// \param p position
                /// \param r relative
                void                        seek_p                  (DToffset p, Relative r);

                /// Change read position
                /// \param p position
                /// \param r relative
                void                        seek_g                  (DToffset g, Relative r);


                /// Return raw pointer to the buffer
                /// \return Buffer pointer
                uint8_t*                    buffer                  (void)                {    return &_stream[0];                            }

                /// Return buffer size
                /// \return buffer size
                DTsize                        size                    (void) const        {    return _logical_size;                        }

                /// Resize buffer
                /// \param size new size of buffer
                void                        resize                  (const DTsize size);

                /// Clear the buffer
                void                        clear                   (void)                {    _logical_size = 0;        _pos_p = _pos_g = 0;    }

                /// Set new buffer contents
                /// \param b raw buffer pointer
                /// \param size size of buffer
                void                        set_buffer              (void *b, DTsize size);

        private:
                void                        grow                    (DTsize size);

                std::vector<uint8_t>        _stream;
                DTsize                        _logical_size;

                DTsize                        _pos_p;
                DTsize                        _pos_g;
};

//==============================================================================
//==============================================================================


} // DT3
