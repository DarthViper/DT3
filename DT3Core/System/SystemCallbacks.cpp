//==============================================================================
///	
///	File: SystemCallbacks.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/System/SystemCallbacks.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

CallbackList<>                                          SystemCallbacks::_screenInitedCB;
CallbackList<uint32_t,uint32_t>                             SystemCallbacks::_screenOpenedCB;
CallbackList<>                                          SystemCallbacks::_screenClosedCB;
CallbackList<>                                          SystemCallbacks::_screenSwapCB;
CallbackList<uint32_t,uint32_t>                             SystemCallbacks::_screenChangedCB;

CallbackList<World*, ComponentBase*>                        SystemCallbacks::_addComponentCB;
CallbackList<World*, ComponentBase*>                        SystemCallbacks::_removeComponentCB;
CallbackList<World*, WorldNode*, WorldNode*, WorldNode*>    SystemCallbacks::_reparentNodeCB;
CallbackList<World*, WorldNode*>                        SystemCallbacks::_addNodeCB;
CallbackList<World*, WorldNode*>                        SystemCallbacks::_removeNodeCB;
CallbackList<World*, Group*>                            SystemCallbacks::_addGroupCB;
CallbackList<World*, Group*>                            SystemCallbacks::_removeGroupCB;

CallbackList<PlugBase*,PlugBase*>                       SystemCallbacks::_connectPlugCB;
CallbackList<PlugBase*,PlugBase*>                       SystemCallbacks::_disconnectPlugCB;
CallbackList<Event*,Event*>                             SystemCallbacks::_connectEventCB;
CallbackList<Event*,Event*>                             SystemCallbacks::_disconnectEventCB;

CallbackList<const TouchEvent*>                         SystemCallbacks::_touchEventCB;
CallbackList<uint32_t,uint16_t>                           SystemCallbacks::_keyDownEventCB;
CallbackList<uint32_t,uint16_t>                           SystemCallbacks::_keyUpEventCB;
CallbackList<>                                          SystemCallbacks::_backButtonEventCB;
CallbackList<>                                          SystemCallbacks::_menuButtonEventCB;

CallbackList<>                                          SystemCallbacks::_beginCaptureMouseCB;
CallbackList<>                                          SystemCallbacks::_endCaptureMouseCB;

CallbackList<const Vector3 &>                           SystemCallbacks::_accelerationEventCB;
CallbackList<const Vector3 &>                           SystemCallbacks::_gyroEventCB;
CallbackList<const Vector3 &>                           SystemCallbacks::_magnetometerEventCB;

CallbackList<>                                          SystemCallbacks::_reloadResourcesCB;
CallbackList<>                                          SystemCallbacks::_emergencyFreeMemoryCB;

CallbackList<const std::string &>                       SystemCallbacks::_errorCB;
CallbackList<const std::string &>                       SystemCallbacks::_messageCB;
CallbackList<const std::string &>                       SystemCallbacks::_debugCB;

//==============================================================================
//==============================================================================



} // DT3
