#ifndef EDSPRITEANIMATIONTRANSFER
#define EDSPRITEANIMATIONTRANSFER
//==============================================================================
///
///	File: EdSpriteAnimationTransferDialog.hpp
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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QTableWidget>

#include "EdSpriteLineEdit.hpp"

//==============================================================================
/// Forward declarations
//==============================================================================

class EdSpriteMainWindow;

//==============================================================================
/// Class
//==============================================================================

class EdSpriteAnimationTransferDialog: public QDialog
{
    Q_OBJECT

    public:
                                        EdSpriteAnimationTransferDialog		(EdSpriteMainWindow *main_window);
                                        ~EdSpriteAnimationTransferDialog    (void);

    public slots:
        void                            onCancel    (void);
        void                            onTransfer  (void);

    private:
        void                            refreshFromAndTo (void);
        void                            refreshTrackInfo (void);

        EdSpriteMainWindow              *_main_window;

        QComboBox                       *_from_animation;
        QComboBox                       *_to_animation;

        struct TrackInfo {
            QString                      _from_track;
            QComboBox                   *_to_track;

            QCheckBox                   *_flip_horz;
            QCheckBox                   *_flip_vert;
        };

        std::vector<TrackInfo>                _track_info;
        QTableWidget                    *_scroll_area;

};

//==============================================================================
//==============================================================================

#endif
