#ifndef EDSPRITENEWEVENTDIALOG
#define EDSPRITENEWEVENTDIALOG
//==============================================================================
///
///	File: EdSpriteNewEventDialog.hpp
///
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>

#include <QtWidgets/QComboBox>

#include "EdSpriteLineEdit.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

class EdSpriteMainWindow;

//==============================================================================
/// Class
//==============================================================================

class EdSpriteNewEventDialog: public QDialog
{
    Q_OBJECT

    public:
                                        EdSpriteNewEventDialog		(EdSpriteMainWindow *main_window);
                                        ~EdSpriteNewEventDialog     (void);

        QString                         getEventID                  (void);
        QString                         getEventParameters          (void);

    public slots:
        void                            onCancel    (void);
        void                            onCreate    (void);

    private:
        EdSpriteMainWindow              *_main_window;

        QComboBox                       *_event_id;
        EdSpriteLineEdit                *_event_parameters;

};

//==============================================================================
//==============================================================================

#endif
