#pragma once
#ifndef EDLEVELCONSOLEWINDOW
#define EDLEVELCONSOLEWINDOW
//==============================================================================
///
///	File: EdLevelConsoleWindow.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Qt include
#include <QtWidgets/QWidget>
#include <QtWidgets/QToolBar>

//==============================================================================
/// Forward declarations
//==============================================================================

class QScrollArea;
class EdLevelDocument;
//==============================================================================
//==============================================================================

namespace Ui {
class EdLevelConsoleWindow;
}
//==============================================================================
/// Class
//==============================================================================

class EdLevelConsoleWindow : public QWidget
{
    Q_OBJECT

    public:
                                    EdLevelConsoleWindow		(QWidget *parent, QToolBar *toolbar, EdLevelDocument *document);
                                    ~EdLevelConsoleWindow       (void);

        /// Description
        /// \param param description
        /// \return description
        void                        append                      (const QString &s);

        /// Description
        /// \param param description
        /// \return description
        void                        logError                    (const std::string &error);

        /// Description
        /// \param param description
        /// \return description
        void                        logMessage                  (const std::string &message);

        /// Description
        /// \param param description
        /// \return description
        void                        logDebug                    (const std::string &debug);


    private:
        EdLevelDocument             *_document;
        QToolBar                    *_toolbar;
        Ui::EdLevelConsoleWindow    *ui;
    protected:
        void changeEvent(QEvent *ev);
    //==========================================================================
    // Qt Signals and slots
    //==========================================================================
    private slots:
        void                        onCommandEntered            ();
        void                        onWriteLog                  (QString msg);

    signals:
        void                        doCommand                   (QString command);
        void                        doWriteLog                  (QString msg);

};

//==============================================================================
//==============================================================================

#endif
