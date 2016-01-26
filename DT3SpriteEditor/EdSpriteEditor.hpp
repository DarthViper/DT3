#ifndef EDSPRITEEDITOR
#define EDSPRITEEDITOR
//==============================================================================
///
///    File: EdSpriteEditor.hpp
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

class EdSpriteEditor : public QGLWidget
{
    Q_OBJECT

    public:
                                        EdSpriteEditor        (EdSpriteMainWindow *main_window, QGLWidget *share = NULL);


    protected:
        void                            draw                (QPainter *painter);

        void                            initializeGL        (void);
        void                            paintGL                (void);
        void                            resizeGL            (int w, int h);

        void                            mousePressEvent        (QMouseEvent *event);
        void                            mouseMoveEvent        (QMouseEvent *event);
        void                            mouseReleaseEvent    (QMouseEvent *event);

        void                            keyPressEvent       (QKeyEvent *event);

    public slots:
        void                            onSpriteChanged     (void);

    private:
        static const float HANDLE_CLICK_SIZE;
        static const float HANDLE_ROTATE_RADIUS;

        enum {
            HANDLE_NONE = 0,
            HANDLE_PLUS_X,
            HANDLE_MINUS_X,
            HANDLE_PLUS_Y,
            HANDLE_MINUS_Y,
            HANDLE_ROTATE,
            HANDLE_POSITION,
            HANDLE_GRID
        };

        void                            drawCube                (const Vector3 &position);
        void                            drawPart                (const Matrix3 &object_to_viewport_transform, KeyedSpriteAnimationPoseJoint *joint, bool selected);
        void                            drawPartSelected        (const Matrix3 &object_to_viewport_transform, KeyedSpriteAnimationPoseJoint *joint, bool selected);
        void                            updateTransforms        (void);

        DT3::Vector2                    getHandleObjectPosition (const KeyedSpriteAnimationPoseJoint *joint, DTint handle);

        DT3::DTint                      getClickedHandle        (const Matrix3 &object_to_viewport_transform, const KeyedSpriteAnimationPoseJoint *joint, int x, int y);
        bool                            isClickedPart           (const Matrix3 &object_to_viewport_transform, const KeyedSpriteAnimationPoseJoint *joint, int x, int y);
        int                             getClickedPart          (const Matrix3 &object_to_viewport_transform, int x, int y);


        EdSpriteMainWindow *            _main_window;

        DT3::MaterialResource           _bounds_material;
        DT3::MaterialResource           _outline_material;
        DT3::MaterialResource           _selected_material;
        DT3::MaterialResource           _handle_material;

        DT3::CameraObject               _camera;
        DT3::DTfloat                    _zoom;
        DT3::Vector2                    _translate;

        DT3::Matrix3                     _object_to_viewport_transform;

        int                                 _current_handle;
        DT3::KeyedSpriteAnimationPoseJoint   *_current_handle_joint;
        int                             _last_mouse_x;
        int                             _last_mouse_y;


};

//==============================================================================
//==============================================================================

#endif
