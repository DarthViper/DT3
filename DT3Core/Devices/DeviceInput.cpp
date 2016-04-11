//==============================================================================
///    
///    File: DeviceInput.cpp
///    
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///    
//==============================================================================

#include "DT3Core/Devices/DeviceInput.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/SystemCallbacks.hpp"
#include "DT3Core/Types/Utility/TouchEvent.hpp"
#include "DT3Core/Types/Math/MoreMath.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION(DeviceInput)

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

DeviceInput::DeviceInput (void)
{

}
                    
DeviceInput::~DeviceInput (void)
{

}

//==============================================================================
//==============================================================================

/// Fires a back button event (Android only)
void DeviceInput::do_back_button (void)
{
    SystemCallbacks::back_button_event_cb().fire();
}

/// Fires a menu button event (Android only)
void DeviceInput::do_menu_button (void)
{
    SystemCallbacks::menu_button_event_cb().fire();
}
        
//==============================================================================
//==============================================================================

/// Sets the current touch state
/// \param event Touch state
void DeviceInput::set_touch_event (TouchEvent *event)
{
    SystemCallbacks::touch_event_cb().fire(event);
    event->cleanup_releases();
    
    
    // Add entropy from random source
    DTfloat x = event->touches[0].pos.x;
    DTfloat y = event->touches[0].pos.y;

    MoreMath::add_entropy ( (uint8_t*) &x, sizeof(x));
    MoreMath::add_entropy ( (uint8_t*) &y, sizeof(y));
}

/// Sets the current keybaord state
/// \param modifiers Bitmask of modifier keys
/// \param key Key code
void DeviceInput::set_key_down_event (uint32_t modifiers, uint16_t key)
{
    SystemCallbacks::key_down_event_cb().fire(modifiers,key);
}

/// Sets the current keybaord state
/// \param modifiers Bitmask of modifier keys
/// \param key Key code
void DeviceInput::set_key_up_event (uint32_t modifiers, uint16_t key)
{
    SystemCallbacks::key_up_event_cb().fire(modifiers,key);
}

/// Sets the current accelerometer state
/// \param a Acceleration
void DeviceInput::set_acceleration_event (const Vector3 &a)
{
    SystemCallbacks::acceleration_cb().fire(a);
    
    // Add entropy from random source
    MoreMath::add_entropy ( (uint8_t*) &a.x, sizeof(a.x));
    MoreMath::add_entropy ( (uint8_t*) &a.y, sizeof(a.y));
    MoreMath::add_entropy ( (uint8_t*) &a.z, sizeof(a.z));
}

/// Sets the current gyro state
/// \param a Rotational acceleration
void DeviceInput::set_gyro_event (const Vector3 &w)
{
    SystemCallbacks::gyro_cb().fire(w);

    // Add entropy from random source
    MoreMath::add_entropy ( (uint8_t*) &w.x, sizeof(w.x));
    MoreMath::add_entropy ( (uint8_t*) &w.y, sizeof(w.y));
    MoreMath::add_entropy ( (uint8_t*) &w.z, sizeof(w.z));
}

/// Sets the current magnetometer state
/// \param a Rotational acceleration
void DeviceInput::set_magnetometer_event (const Vector3 &m)
{
    SystemCallbacks::magnetometer_cb().fire(m);

    // Add entropy from random source
    MoreMath::add_entropy ( (uint8_t*) &m.x, sizeof(m.x));
    MoreMath::add_entropy ( (uint8_t*) &m.y, sizeof(m.y));
    MoreMath::add_entropy ( (uint8_t*) &m.z, sizeof(m.z));
}

//==============================================================================
//==============================================================================

/// Call to begin mouse capture
void DeviceInput::begin_capture_mouse (void)
{
    DT3::SystemCallbacks::begin_capture_mouse_cb().fire();
}

/// Call to begin mouse capture
void DeviceInput::end_capture_mouse (void)
{
    DT3::SystemCallbacks::end_capture_mouse_cb().fire();
}

//==============================================================================
//==============================================================================
        

} // DT3
