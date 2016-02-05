//==============================================================================
///	
///	File: Vector3.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Types/Math/Vector3.hpp"
#include "DT3Core/Types/Math/Vector2.hpp"
#include "DT3Core/Types/Math/Vector4.hpp"
#include "DT3Core/Types/FileBuffer/Stream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

Vector3 Vector3::fromVec4(const Vector4 &rhs)
{   
    return {rhs.x,rhs.y,rhs.z};
}

Vector3 Vector3::fromVec2(Vector2 rhs, float z_) { return Vector3 {rhs.x,rhs.y,z_}; }

//==============================================================================
//==============================================================================

Stream& operator <<(Stream &s, const Vector3&v)
{
	s << v.x << Stream::fs << v.y << Stream::fs << v.z;
	return s;
}

Stream& operator >>(Stream &s, Vector3&v)
{
	DTfloat x=v.x,y=v.y,z=v.z;
	s >> x >> y >> z;
	
	v.x = (x);
	v.y = (y);
	v.z = (z);
	
	return s;
}

//==============================================================================
//==============================================================================

/// Cross product of two vectors
/// \param a Vector 1
/// \param b Vector 2
/// \return Cross product
Vector3 Vector3::cross (Vector3 a, Vector3 b)
{
    return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
    };
    
}
Vector3 testMe(Vector3 x) {
    return Vector3::cross(x,Vector3::cross(x,{0,1,1}));
}
//==============================================================================
//==============================================================================

/// Displaces a position along a normal by and amount of the 3rd param
/// \param a position
/// \param b normal
/// \param c amount
void Vector3::displace (const Vector3 &a, const Vector3 &n, DTfloat d, Vector3 &r)
{
    DTfloat x = a.x + n.x * d;
    DTfloat y = a.y + n.y * d;
    DTfloat z = a.z + n.z * d;

    r.x = x;
    r.y = y;
    r.z = z;
}

//==============================================================================
//==============================================================================

/// Reflects a vector around a normal with a certain restitution
void Vector3::reflect (const Vector3 &dir, const Vector3 &n, const DTfloat restitution, Vector3 &r)
{
    Vector3 delta;
    DTfloat dot;
    
    dot = Vector3::dot(dir, n);
    r = dir + n * (-(dot + dot * restitution));
}

//==============================================================================
//==============================================================================
		
} // DT3

