//==============================================================================
///
///    File: EdLevelConsoleWindow.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelConsoleWindow.hpp"
#include "EdLevelDocument.hpp"
#include "EdLevelLineEdit.hpp"
#include "ui_EdLevelConsoleWindow.h"

// Qt include
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtGui/QFont>

// Engine includes
#include "DT3Core/System/SystemCallbacks.hpp"

//==============================================================================
//==============================================================================

using namespace DT3;

//==============================================================================
//==============================================================================

EdLevelConsoleWindow::EdLevelConsoleWindow(QWidget *parent, QToolBar *toolbar, EdLevelDocument *document)
    :   QWidget                 (parent), ui(new Ui::EdLevelConsoleWindow)
{
    _document = document;
    _toolbar = toolbar;
    ui->setupUi(this);

    connect(this, SIGNAL(doWriteLog(QString)), this, SLOT(onWriteLog(QString)));

    SystemCallbacks::error_cb().add(make_callback(this, &EdLevelConsoleWindow::logError));
    SystemCallbacks::message_cb().add(make_callback(this, &EdLevelConsoleWindow::logMessage));
    SystemCallbacks::debug_cb().add(make_callback(this, &EdLevelConsoleWindow::logDebug));
}

EdLevelConsoleWindow::~EdLevelConsoleWindow(void)
{
    SystemCallbacks::error_cb().remove(make_callback(this, &EdLevelConsoleWindow::logError));
    SystemCallbacks::message_cb().remove(make_callback(this, &EdLevelConsoleWindow::logMessage));
    SystemCallbacks::debug_cb().remove(make_callback(this, &EdLevelConsoleWindow::logDebug));
}

//==============================================================================
//==============================================================================

void EdLevelConsoleWindow::onCommandEntered()
{
    emit doCommand(ui->_command_widget->text());
    ui->_command_widget->setText("");
}

//==============================================================================
//==============================================================================

void EdLevelConsoleWindow::append (const QString &s)
{
    emit doWriteLog(s);
}

//==============================================================================
//==============================================================================

void EdLevelConsoleWindow::logError(const std::string &error)
{
    emit doWriteLog((std::string("ERR: ") + error).c_str());
}

void EdLevelConsoleWindow::logMessage(const std::string &message)
{
    emit doWriteLog((std::string("MSG: ") + message).c_str());
}

void EdLevelConsoleWindow::logDebug(const std::string &debug)
{
    emit doWriteLog((std::string("DBG: ") + debug).c_str());
}

//==============================================================================
//==============================================================================

void EdLevelConsoleWindow::onWriteLog (QString msg)
{
    ui->_console->appendPlainText(msg);
    ui->_console->verticalScrollBar()->setValue(ui->_console->verticalScrollBar()->maximum());
}

void EdLevelConsoleWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
//==============================================================================
//==============================================================================

