#pragma once
//==============================================================================
///
///    File: EdLevelToolWindow.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Qt include
#include <QtOpenGL/QGLWidget>

class EdLevelDocument;
//==============================================================================
/// Class
//==============================================================================

class EdLevelToolWindow : public QGLWidget
{
    Q_OBJECT

    public:
                                        EdLevelToolWindow       (QWidget *parent, EdLevelDocument *document);

    public Q_SLOTS:
        void                            onCommand               (QString command);
    Q_SIGNALS:
        void                            doCommand              (QString command);
};

//==============================================================================
//==============================================================================
