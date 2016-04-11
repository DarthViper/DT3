//==============================================================================
///
///    File: EdLevelAppMain.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelAppMain.hpp"
#include "EdLevelMainWindow.hpp"

// Qt include
#include <QtCore/QFile>
#include <QtWidgets/QApplication>

// Engine includes
#include "DT3Core/Entry/GameMainThread.hpp"

//==============================================================================
//==============================================================================

int main(int argc, char *argv[])
{
    //   scriptingTimerReferer();
    DT3::GameMainThread::initialize_engine();

    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QApplication::setStyle("fusion");

    // Set style sheet
    QFile file(":/LevelEditor.qss");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString style_sheet = file.readAll();
    file.close();

    QApplication app(argc, argv);
    app.setStyleSheet(style_sheet);

    EdLevelMainWindow *window = new EdLevelMainWindow();
    window->show();

    app.exec();

    DT3::GameMainThread::destroy_engine();
}

//==============================================================================
//==============================================================================
