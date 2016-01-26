#ifndef EDSPRITEUVEDITOR
#define EDSPRITEUVEDITOR
//==============================================================================
///
///	File: EdSpriteUVEditor.hpp
///
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include <QtOpenGL/QGLWidget>
#include "EdSpriteMainWindow.hpp"
#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
#include "DT3Core/Objects/CameraObject.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

//==============================================================================
/// Class
//==============================================================================

class EdSpriteUVEditor : public QGLWidget
{
    Q_OBJECT

    public:
                                        EdSpriteUVEditor    (EdSpriteMainWindow *main_window, QGLWidget *share = NULL);


    protected:
        void							draw				(QPainter *painter);

        void							initializeGL		(void);
        void							paintGL				(void);
        void							resizeGL			(int w, int h);

        void							mousePressEvent		(QMouseEvent *event);
        void							mouseMoveEvent		(QMouseEvent *event);
        void							mouseReleaseEvent	(QMouseEvent *event);

        void                            keyPressEvent       (QKeyEvent *event);

    public slots:
        void                            onSpriteChanged     (void);

    private:
        static const float HANDLE_CLICK_SIZE;
        static const float HANDLE_ROTATE_RADIUS;

        enum HandleID {
            HANDLE_NONE = 0,
            HANDLE_PLUS_U,
            HANDLE_MINUS_U,
            HANDLE_PLUS_V,
            HANDLE_MINUS_V
        };

        void                            drawCube                (const DT3::Vector3 &position);
        void                            drawPart                (const DT3::Matrix3 &object_to_viewport_transform, DT3::KeyedSpriteAnimationPoseJoint *joint, bool selected);
        void                            updateTransforms        (void);

        Vector2                         getHandleObjectPosition (const DT3::KeyedSpriteAnimationPoseJoint *joint, HandleID handle);

        HandleID                        getClickedHandle        (const DT3::Matrix3 &object_to_viewport_transform, const DT3::KeyedSpriteAnimationPoseJoint *joint, int x, int y);
        bool                            isClickedPart           (const DT3::Matrix3 &object_to_viewport_transform, const DT3::KeyedSpriteAnimationPoseJoint *joint, int x, int y);
        int                             getClickedPart          (const DT3::Matrix3 &object_to_viewport_transform, int x, int y);


        EdSpriteMainWindow              *_main_window;

        DT3::MaterialResource                _bounds_material;
        DT3::MaterialResource                _outline_material;
        DT3::MaterialResource                _selected_material;
        DT3::MaterialResource                _handle_material;

        DT3::CameraObject                    _camera;
        DT3::DTfloat                         _zoom;
        DT3::Vector2                         _translate;

        DT3::Matrix3                         _object_to_viewport_transform;

        int                             _current_handle;
        DT3::KeyedSpriteAnimationPoseJoint   *_current_handle_part;
        int                             _last_mouse_x;
        int                             _last_mouse_y;


};

//==============================================================================
//==============================================================================

#endif
