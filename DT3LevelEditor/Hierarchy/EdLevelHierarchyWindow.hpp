#pragma once
//==============================================================================
///
///    File: EdLevelHierarchyWindow.hpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "EdLevelLineEdit.hpp"

// Qt include
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QToolBar>
#include <QtCore/QTimer>
#include <QtCore/QRegExp>

#include <memory>

//==============================================================================
/// Forward declarations
//==============================================================================

namespace DT3 {
    class WorldNode;
    class PlugNode;
    class PlugBase;
    class Event;
    class ComponentBase;
}
class EdLevelDocument;

//==============================================================================
//==============================================================================

//==============================================================================
/// Class
//==============================================================================

class EdLevelHierarchyWindow : public QTreeWidget
{
    Q_OBJECT

    public:
                                        EdLevelHierarchyWindow        (QWidget *parent, QToolBar *toolbar, EdLevelDocument *document);

        void                            selectionChanged            (const QItemSelection & selected, const QItemSelection & deselected);


        Qt::DropActions                 supportedDropActions        (void) const    {   return Qt::MoveAction;  }

        QMimeData*                      mimeData                    (const QList<QTreeWidgetItem *> items) const;
        QStringList                     mimeTypes                   (void) const;

        bool                            dropMimeData                (QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action);
        void                            dropEvent                   (QDropEvent *event);

        void                            dragEnterEvent              (QDragEnterEvent *event);
        void                            dragLeaveEvent              (QDragLeaveEvent *event);
        void                            dragMoveEvent               (QDragMoveEvent *event);

        void                            keyPressEvent               (QKeyEvent *event);

    private:
        static constexpr const int AUTO_SCROLL_TIMER = 30;
        static constexpr const int AUTO_SCROLL_MARIGN = 30;

        EdLevelDocument                 *_document;
        EdLevelLineEdit                 *_filter;
        QToolBar                        *_toolbar;
        QTreeWidgetItem                 *_top_level;

        QAction                         *_show_objects;
        QAction                         *_show_scripting;
        QAction                         *_show_all;
        QRegExp                         _reg_exp_filter;

        void                            startAutoScroll             (void);
        void                            stopAutoScroll              (void);

        QTimer                          _auto_scroll_timer;
        int                             _auto_scroll_x;
        int                             _auto_scroll_y;

        // Internal representation of scene
        struct NodeCache {
            NodeCache(const std::shared_ptr<DT3::WorldNode> &node)       {   _node = node; }

            bool   operator == (const NodeCache& rhs) const    {    return _node == rhs._node;        }

            std::shared_ptr<DT3::WorldNode>      _node;
            QTreeWidgetItem                 *_list_object=nullptr;
        };

        std::list<NodeCache>                _node_cache;

        std::shared_ptr<DT3::WorldNode> itemToNode                  (const QTreeWidgetItem *item) const;

        QTreeWidgetItem*                nodeToItem                  (DT3::WorldNode *node) const;
        QTreeWidgetItem*                nodeToItem                  (const std::shared_ptr<DT3::WorldNode> &node) const;


        enum Visibility {
            VIS_ALL,
            VIS_OBJECTS,
            VIS_SCRIPTING
        } _visibility;

        void                            setVisibility               (NodeCache *c);

    public slots:
        void                            onAddNode                   (DT3::WorldNode *node);
        void                            onRemoveNode                (DT3::WorldNode *node);
        void                            onReparentNode              (DT3::WorldNode *node, DT3::WorldNode *old_parent, DT3::WorldNode *new_parent);

        void                            onRefreshHierarchy          (void);
        void                            onSelectionChanged          (const std::list<std::shared_ptr<DT3::PlugNode>> &selection_list);

        void                            onConnectPlug               (DT3::PlugBase *outgoing, DT3::PlugBase *incoming);
        void                            onDisconnectPlug            (DT3::PlugBase *outgoing, DT3::PlugBase *incoming);
        void                            onConnectEvent              (DT3::Event *outgoing, DT3::Event *incoming);
        void                            onDisconnectEvent           (DT3::Event *outgoing, DT3::Event *incoming);

        void                            onShowObjects               (void);
        void                            onShowCalc                  (void);
        void                            onShowAll                   (void);
        void                            onShowFilter                (const QString & text);

        void                            onAutoScroll                (void);

        void                            onItemChanged               (QTreeWidgetItem *item, int column);

    signals:
        void                            doCommand                   (QString command);
        void                            doUndoBlock                 (void);
        void                            doSelectionChanged          (const std::list<std::shared_ptr<DT3::PlugNode>> &selection_list);
};

//==============================================================================
//==============================================================================
