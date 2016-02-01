#pragma once
//==============================================================================
///
///	File: EdLevelLineEdit.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Qt include
#include <QtWidgets/QLineEdit>

//==============================================================================
/// Forward declarations
//==============================================================================

class QKeyEvent;

//==============================================================================
/// Class
//==============================================================================

class EdLevelLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    EdLevelLineEdit (QWidget *parent);

    virtual void        keyPressEvent (QKeyEvent *event);
};

//==============================================================================
//==============================================================================
