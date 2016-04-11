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

                Stream&                     operator<<              (const Stream::FS) override {    return *this;    }
                Stream&                     operator<<              (const bool n) override;
                Stream&                     operator<<              (const int8_t n) override;
                Stream&                     operator<<              (const int16_t n) override;
                Stream&                     operator<<              (const int32_t n) override;
                Stream&                     operator<<              (const uint8_t n) override;
                Stream&                     operator<<              (const uint16_t n) override;
                Stream&                     operator<<              (const uint32_t n) override;
                Stream&                     operator<<              (const int64_t n) override;
                Stream&                     operator<<              (const uint64_t n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                     operator<<              (const DTsize n) override;
#endif
                Stream&                     operator<<              (const DTfloat n) override;
                Stream&                     operator<<              (const DTdouble n) override;
                Stream&                     operator<<              (const DTlonglong n) override;
                Stream&                     operator<<              (const DTcharacter n) override;
                Stream&                     operator<<              (const char* n) override;
                Stream&                     operator<<              (const std::string &n) override;
                Stream&                     operator<<              (const BinaryBufferStream& n);


                Stream&                     operator>>              (bool &n) override;
                Stream&                     operator>>              (int8_t &n) override;
                Stream&                     operator>>              (int16_t &n) override;
                Stream&                     operator>>              (int32_t &n) override;
                Stream&                     operator>>              (uint8_t &n) override;
                Stream&                     operator>>              (uint16_t &n) override;
                Stream&                     operator>>              (uint32_t &n) override;
                Stream&                     operator>>              (int64_t &n) override;
                Stream&                     operator>>              (uint64_t &n) override;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                Stream&                     operator>>              (DTsize &n) override;
#endif
                Stream&                     operator>>              (DTfloat &n) override;
                Stream&                     operator>>              (DTdouble &n) override;
                Stream&                     operator>>              (DTlonglong &n) override;
                Stream&                     operator>>              (DTcharacter &n) override;
                Stream&                     operator>>              (std::string &n) override;


                /// Return write position
                /// \return write position
                DTsize                        p                       (void) override;

                /// Return read position
                /// \return read position
                DTsize                        g                       (void) override;

                /// Change write position
                /// \param p position
                /// \param r relative
                void                        seek_p                  (DToffset p, Relative r) override;

                /// Change read position
                /// \param p position
                /// \param r relative
                void                        seek_g                  (DToffset g, Relative r) override;


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
