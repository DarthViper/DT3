#pragma once
#ifndef EDLEVELTOOLEVENT
#define EDLEVELTOOLEVENT
//==============================================================================
///
///	File: EdLevelToolEvent.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include

// Qt include

// Engine includes
#include "DT3Core/Types/Base/BaseInclude.hpp"
#include "DT3Core/Types/Math/Vector3.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

namespace DT3 {
    class CameraObject;
}

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
/// Class
//==============================================================================

class EdLevelToolEvent
{
    public:
                                                EdLevelToolEvent        (void);
                                                EdLevelToolEvent		(const EdLevelToolEvent &rhs);
        EdLevelToolEvent &                      operator =              (const EdLevelToolEvent &rhs);
        virtual                                 ~EdLevelToolEvent       (void);

    public:

        Vector3                                 getRaySource            (void) const    {   return _ray_src;        }
        Vector3                                 getRayDestination       (void) const    {   return _ray_dest;       }

        unsigned int                                  mouseX                  (void) const    {   return _mouse_x;        }
        unsigned int                                  mouseY                  (void) const    {   return _mouse_y;        }

        const std::shared_ptr<CameraObject>&    getCamera               (void) const    {   return _camera;         }

        float                                   getGrid                 (void) const    {   return _grid;           }

        unsigned int                                  keyCode                 (void) const    {   return _key_code;       }
        unsigned int                                  modifiers               (void) const    {   return _modifiers;      }

    public:
        static const int MODIFIER_SHIFT;
        static const int MODIFIER_CONTROL;
        static const int MODIFIER_OPTION_ALT;
        static const int MODIFIER_META;

        enum EventType {
            NONE,
            MOUSE_DOWN,
            MOUSE_DRAG,
            MOUSE_UP,
            KEY_DOWN
        };
        EventType                       _event_type;

        std::shared_ptr<CameraObject>   _camera;
        Vector3                         _ray_src;
        Vector3                         _ray_dest;

        unsigned int                          _control_id;

        unsigned int                          _mouse_x;
        unsigned int                          _mouse_y;

        unsigned int                          _key_code;
        unsigned int                          _modifiers;

        unsigned int                          _window_width;
        unsigned int                          _window_height;

        float                         _grid;
};

//==============================================================================
//==============================================================================

#endif
