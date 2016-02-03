#pragma once
#ifndef DT3_STREAM
#define DT3_STREAM
//==============================================================================
///
///	File: Stream.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseClass.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Class
//==============================================================================

class Stream: public BaseClass {
    public:
        DEFINE_TYPE(Stream,BaseClass)
                //DEFINE_CREATE_AND_CLONE

                                    Stream				(void);
        private:
                                    Stream				(const Stream &rhs);
        Stream &					operator =			(const Stream &rhs);
    public:
        virtual						~Stream				(void);

        public:
                // Tokens for streaming
            enum FS {
            fs
        };


                virtual Stream&				operator<<			(const FS) = 0;
                virtual Stream&				operator<<			(const bool n) = 0;
                virtual Stream&				operator<<			(const int8_t n) = 0;
                virtual Stream&				operator<<			(const int16_t n) = 0;
                virtual Stream&				operator<<			(const int32_t n) = 0;
                virtual Stream&				operator<<			(const uint8_t n) = 0;
                virtual Stream&				operator<<			(const uint16_t n) = 0;
                virtual Stream&				operator<<			(const uint32_t n) = 0;
                virtual Stream&				operator<<			(const int64_t n) = 0;
                virtual Stream&				operator<<			(const uint64_t n) = 0;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                virtual Stream&				operator<<			(const DTsize n) = 0;
#endif
                virtual Stream&				operator<<			(const DTfloat n) = 0;
                virtual Stream&				operator<<			(const DTdouble n) = 0;
                virtual Stream&				operator<<			(const DTlonglong n) = 0;
                virtual Stream&				operator<<			(const DTcharacter n) = 0;
                virtual Stream&				operator<<			(const char* n) = 0;
                virtual Stream&				operator<<			(const std::string &n) = 0;

        // Takes care of enums
        template <typename T>
        Stream&                     operator<<          (const T &v)                    {   operator << ( (int32_t) v );  return *this;   }



                virtual Stream&				operator>>			(bool &n) = 0;
                virtual Stream&				operator>>			(int8_t &n) = 0;
                virtual Stream&				operator>>			(int16_t &n) = 0;
                virtual Stream&				operator>>			(int32_t &n) = 0;
                virtual Stream&				operator>>			(uint8_t &n) = 0;
                virtual Stream&				operator>>			(uint16_t &n) = 0;
                virtual Stream&				operator>>			(uint32_t &n) = 0;
                virtual Stream&				operator>>			(int64_t &n) = 0;
                virtual Stream&				operator>>			(uint64_t &n) = 0;
#if DT3_SIZES_ARE_DISTINCT_TYPES
                virtual Stream&				operator>>			(DTsize &n) = 0;
#endif
                virtual Stream&				operator>>			(DTfloat &n) = 0;
                virtual Stream&				operator>>			(DTdouble &n) = 0;
                virtual Stream&				operator>>			(DTlonglong &n) = 0;
                virtual Stream&				operator>>			(DTcharacter &n) = 0;
                virtual Stream&				operator>>			(std::string &n) = 0;

        // Takes care of enums
        template <typename T>
        Stream&                     operator>>          (T &v)  {   int32_t vi;
                                                                    operator >> (vi);
                                                                    v = (T) vi;
                                                                    return *this;   }



        enum Relative {
                        FROM_BEGINNING,
                        FROM_END,
                        FROM_CURRENT
                };

                /// Return write position
                /// \return write position
                virtual DTsize              p                   (void) = 0;

                /// Return read position
                /// \return read position
                virtual DTsize              g                   (void) = 0;

                /// Change write position
                /// \param p position
                /// \param r relative
                virtual void                seek_p              (DToffset p, Relative r) = 0;

                /// Change read position
                /// \param p position
                /// \param r relative
                virtual void                seek_g              (DToffset g, Relative r) = 0;

};

//==============================================================================
/// Streaming operators
//==============================================================================

template <typename T>
Stream& operator <<(Stream &s, const std::shared_ptr<T> &r) {   return s;   }

template <typename T>
Stream& operator >>(Stream &s, std::shared_ptr<T> &r)       {   return s;   }

//==============================================================================
//==============================================================================


} // DT3

#endif
