#pragma once
//==============================================================================
///
///	File: Vector.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Utility/Assert.hpp"
#include "DT3Core/Types/Utility/TypeTraits.hpp"
#include <cmath>

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Forward declarations
//==============================================================================

class Stream;
class Vector3;
class Vector4;

//==============================================================================
/// Class
//==============================================================================

class Vector2 {
    public:
        DEFINE_TYPE_SIMPLE_BASE(Vector2)

    public:
            static Vector2 fromVector3(Vector3 src);
            static Vector2 fromVector4(Vector4 rhs);
        /// Description
        /// \param param description
        /// \return description
        inline bool	operator ==				(Vector2 rhs) const  {   return x == rhs.x && y == rhs.y;		}

        /// Description
        /// \param param description
        /// \return description
        inline bool	operator !=				(Vector2 rhs) const  {	return x != rhs.x || y != rhs.y;		}


        /// Description
        /// \param param description
        /// \return description
        Vector2 &			operator *=				(const DTfloat rhs)			{	x*=rhs;		y*=rhs;     return *this;	}

        /// Description
        /// \param param description
        /// \return description
        Vector2 &			operator /=				(const DTfloat rhs)			{	x/=rhs;		y/=rhs;     return *this;	}

        /// Description
        /// \param param description
        /// \return description
        inline Vector2 &    operator +=				(Vector2 rhs)		{	x+=rhs.x;	y+=rhs.y;   return *this;	}

        /// Description
        /// \param param description
        /// \return description
        inline Vector2 &    operator -=				(Vector2 rhs)		{	x-=rhs.x;	y-=rhs.y;   return *this;	}

        /// Set each of the components to zero
        void				clear					(void)						{	x = y = 0.0F;							}

        /// Returns the magnitude of the vector
        /// \return magnitude of the vector
        inline DTfloat      abs						(void) const				{   return std::sqrt(x*x + y*y);            }

        /// Returns the magnitude^2 of the vector
        /// \return magnitude^2 of the vector
        inline DTfloat      abs2					(void) const				{   return x*x + y*y;						}

        /// Returns a normalized copy of the vector
        /// \return normalized vector
        Vector2				normalized				(void) const				{	DTfloat absv = abs();   ASSERT(absv != 0.0F);   return {x/absv,y/absv};      }

        /// Normalizes the vector in place
        void                normalize				(void)						{	DTfloat absv = abs();   ASSERT(absv != 0.0F);   (*this) = {x/absv,y/absv};   }

        /// Return perped copy of the vector
        /// \return perped copy of the vector
        inline Vector2      perped					(void) const        {   return {-y,x};			}

        ///  Perp the vector in place
        inline void         perp					(void)						{   (*this) = {-y,x};        }


        /// Dot product of two vectors
        /// \param a Vector 1
        /// \param b Vector 2
        /// \return Dot product
        static DTfloat		dot						(Vector2 a, Vector2 b)	{	return a.x*b.x + a.y*b.y;		}

        /// perp dot (like 2D cross product) of two vectors
        /// \param a Vector 1
        /// \param b Vector 2
        /// \return Perp Dot product
        static DTfloat		perp_dot                (Vector2 a, Vector2 b)    {	return a.x * b.y - a.y * b.x;	}

    public:
            DTfloat x;
            DTfloat y;
};

//==============================================================================
/// Streaming operators
//==============================================================================

Stream& operator <<(Stream &s, const Vector2&v);
Stream& operator >>(Stream &s, Vector2&v);

//==============================================================================
//==============================================================================

inline Vector2 operator + (Vector2 a, Vector2 b)
{
    return {a.x + b.x, a.y + b.y};
}

inline Vector2 operator - (Vector2 a, Vector2 b)
{
    return {a.x - b.x, a.y - b.y};
}

inline Vector2 operator - (Vector2 a)
{
    return {-a.x, -a.y};
}

inline Vector2 operator * (const DTfloat a, Vector2 b)
{
    return {b.x * a, b.y * a};
}

inline Vector2 operator * (Vector2 a, const DTfloat b)
{
    return {a.x * b, a.y * b};
}

inline Vector2 operator * (Vector2 a, Vector2 b)
{
    return {a.x * b.x, a.y * b.y};
}

inline Vector2 operator / (Vector2 a, const DTfloat b)
{
    return {a.x / b, a.y / b};
}

//==============================================================================
// Info classes for Traits
//==============================================================================

namespace TypeTraitsInfo {

template <> struct Info<Vector2> {
    static Vector2				default_value(void)	{	return {0.0F,0.0F};			}
    static const DTcharacter*	name(void)          {	return "Vector2";}
    static const DTcharacter*	name_caps(void)     {	return "Vector2";}
    enum { isFundamental = 0 };
};

} // TypeTraitsInfo

//==============================================================================
//==============================================================================

} // DT3
