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

#include "DT3Core/Types/Math/Vector2.hpp"
#include "DT3Core/Types/Math/Vector3.hpp"
#include "DT3Core/Types/Math/Vector4.hpp"
#include "DT3Core/Types/FileBuffer/Stream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

Vector2 Vector2::fromVector3(Vector3 rhs)
{   
    return {rhs.x,rhs.y};
}

Vector2 Vector2::fromVector4 (Vector4 rhs)
{   
    return {rhs.x,rhs.y};
}

//==============================================================================
//==============================================================================

Stream& operator <<(Stream &s, const Vector2 &v)
{
	s << v.x << Stream::fs << v.y;
	return s;
}

Stream& operator >>(Stream &s, Vector2 &v)
{
	s >> v.x >> v.y;
	return s;
}

//==============================================================================
//==============================================================================
		
} // DT3

