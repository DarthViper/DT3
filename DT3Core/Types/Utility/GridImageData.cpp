//==============================================================================
///    
///    File: GridImageData.cpp
///    
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///    
//==============================================================================

#include "DT3Core/Types/Utility/GridImageData.hpp"
#include "DT3Core/Types/FileBuffer/Stream.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

//IMPLEMENT_FACTORY_CREATION(GridImageData)

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

GridImageData::GridImageData (void)
    :   _num_x  (5),
        _num_y  (5)
{  
    clear();
}
        
GridImageData::GridImageData (const GridImageData &rhs)
    :   _num_x  (rhs._num_x),
        _num_y  (rhs._num_y),
        _grid   (rhs._grid)
{   

}

GridImageData & GridImageData::operator = (const GridImageData &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {
        _num_x = rhs._num_x;
        _num_y = rhs._num_y;
        _grid = rhs._grid;
    }
    return (*this);
}
            
GridImageData::~GridImageData (void)
{

}

//==============================================================================
//==============================================================================

Stream& operator << (Stream &s, const GridImageData&v)
{
    s << v._num_x << Stream::fs << v._num_y << Stream::fs;
    
    for (auto &grid : v._grid) {
        s << grid.x << Stream::fs << grid.y << Stream::fs;
    }
    

    return s;
}

Stream& operator >> (Stream &s, GridImageData&v)
{
    s >> v._num_x >> v._num_y;
    v.clear();
    
    for (auto &grid : v._grid) {
        s >> grid.x;
        s >> grid.y;
    }
    
    return s;
}

//==============================================================================
//==============================================================================

void GridImageData::clear (void)
{
    if (_grid.size() != _num_x * _num_y) {
        _grid.clear();
        _grid.resize(_num_x * _num_y, {0.0F,0.0F});
    }

    // Init array
    for (uint32_t y = 0; y < _num_y; ++y) {
        for (uint32_t x = 0; x < _num_x; ++x) {
            DTfloat xpos = static_cast<DTfloat>(x) / (_num_x - 1) * 2.0F - 1.0F;
            DTfloat ypos = static_cast<DTfloat>(y) / (_num_y - 1) * 2.0F - 1.0F;
        
            set_point (x, y, {xpos, ypos});
        }
    }
}

//==============================================================================
//==============================================================================

void GridImageData::set_num_x (const uint32_t num_x)
{
    _num_x = num_x;
    
    clear();
}

uint32_t GridImageData::num_x(void) const
{
    return _num_x;
}

void GridImageData::set_num_y (const uint32_t num_y)
{
    _num_y = num_y;

    clear();
}

uint32_t GridImageData::num_y(void) const
{
    return _num_y;
}

//==============================================================================
//==============================================================================

const Vector2 & GridImageData::point (uint32_t x, uint32_t y)
{
    return _grid[y * _num_x + x];
}

void GridImageData::set_point (uint32_t x, uint32_t y, const Vector2 &p)
{
    _grid[y * _num_x + x] = p;
}

//==============================================================================
//==============================================================================

} // DT3

