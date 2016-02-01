//==============================================================================
///
///	File: EdLevelWorldWindow.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

// Editor include
#include "WorldWindow.h"
#include "ui_WorldWindow.h"
#include "EdLevelDocument.hpp"
#include "EdLevelToolEvent.hpp"
#include "EdLevelTool.hpp"
#include "EdLevelManipPan.hpp"
#include "EdLevelManipRotate.hpp"
#include "EdLevelManipScale.hpp"
#include "EditorObjectFactory.h"
#include "EngineObjectTools.h"

// Qt include
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtCore/QFile>
#include <QtCore/QDebug>

// Engine includes
#include "DT3Core/World/World.hpp"
#include "DT3Core/Entry/GameMainThread.hpp"
#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
#include "DT3Core/Resources/ResourceTypes/ShaderResource.hpp"
#include "DT3Core/Objects/CameraObject.hpp"
#include "DT3Core/World/WorldNode.hpp"
#include "DT3Core/System/System.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/Types/Graphics/DrawBatcher.hpp"
#include "DT3Core/Types/Math/MoreMath.hpp"
#include "DT3Core/Types/Graphics/DrawUtils.hpp"
#include "DT3Core/Types/Utility/ConsoleStream.hpp"
#include <iostream>

//==============================================================================
//==============================================================================

using namespace DT3;
//==============================================================================
//==============================================================================
static QStringList resolutionList = {
    "Full Resolution",
    "1024x768 (iPad Landscape)",
    "768x1024 (iPad Portrait)",
    "960x640 (iPhone 4 Landscape)",
    "640x960 (iPhone 4 Portrait)",
    "480x320 (HVGA, iPhone 3GS Landscape)",
    "320x480 (HVGA, iPhone 3GS Portrait)",
    "2048x1536 (iPad3 Landscape)",
    "1536x2048 (iPad3 Portrait)",
    //_resolution_selection->insertSeparator(_resolution_selection->count(),
    "2560x1600 (Landscape)",
    "1600x2560 (Portrait)",
    "2560x1536 (Landscape)",
    "1536x2560 (Portrait)",
    "1920x1200 (Landscape)",
    "1200x1920 (Portrait)",
    "1920x1152 (Landscape)",
    "1152x1920 (Portrait)",
    "1536x1152 (Landscape)",
    "1152x1536 (Portrait)",
    "1280x800 (Xoom, Galaxy Tab 10.1, WXGA Landscape)",
    "800x1280 (Xoom, Galaxy Tab 10.1, WXGA Portrait)",
    "1280x768 (Landscape)",
    "768x1280 (Portrait)",
    "1024x580 (Kindle Landscape)",
    "580x1024 (Kindle Portrait)",
    "1024x600 (Galaxy Tab)",
    "600x1024 (Galaxy Tab)",
    "854x480 (WVGA854 Landscape)",
    "480x854 (WVGA854 Portrait)",
    "800x480 (Galaxy S II, WVGA800 Landscape)",
    "480x800 (Galaxy S II, WVGA800 Portrait)",
    "540x460 (Landscape)",
    "460x540 (Portrait)",
    "432x240 (FWQVGA Landscape)",
    "240x432 (FWQVGA Portrait)",
    "400x240 (WQVGA Landscape)",
    "240x400 (WQVGA Portrait)",
    "320x240 (QVGA Landscape)",
    "240x320 (QVGA Portrait)",
    //_resolution_selection->insertSeparator(_resolution_selection->count(),
    "1280x720 (HD720p)",
    "1920x1080 (HD1080p)"
};
WorldWindow::WorldWindow(QWidget *parent, QToolBar *toolbar, EdLevelDocument *document)
    :   QGLWidget       (parent),
        _camera                 (NULL),
        _tool                   (NULL),
        _built_in_zoom          (100.0F),
        _builtin_camera_index   (-1),
        _custom_camera_index    (-1),
        ui(new Ui::WorldWindow)
{
    void (QComboBox:: *combo_activated_int)(int) = &QComboBox::activated;

    ui->setupUi(this);

    EditorObjectFactory::registerClass<EdLevelManipPan>();
    EditorObjectFactory::registerClass<EdLevelManipRotate>();
    EditorObjectFactory::registerClass<EdLevelManipScale>();

    _document = document;
    _toolbar = toolbar;

    //
    // Actions and toolbar
    //

    connect(ui->_arrow_action, SIGNAL(triggered()), this, SLOT(onArrowTool()));
    connect(ui->_pan_action, SIGNAL(triggered()), this, SLOT(onPanTool()));
    connect(ui->_rotate_action, SIGNAL(triggered()), this, SLOT(onRotateTool()));
    connect(ui->_scale_action, SIGNAL(triggered()), this, SLOT(onScaleTool()));


    toolbar->addAction(ui->_arrow_action);
    toolbar->addAction(ui->_pan_action);
    toolbar->addAction(ui->_rotate_action);
    toolbar->addAction(ui->_scale_action);

    QWidget *spacer1 = new QWidget(toolbar);
    spacer1->setMinimumWidth(10);
    toolbar->addWidget(spacer1);

    QLabel *camera_selection_label = new QLabel("Camera:",toolbar);
    camera_selection_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    toolbar->addWidget(camera_selection_label);

    _camera_selection = new QComboBox(toolbar);
    _camera_selection->setMinimumWidth(150);

    connect(_camera_selection, combo_activated_int, this, &WorldWindow::onChangeCamera	);

    toolbar->addWidget(_camera_selection);


    QWidget *spacer2 = new QWidget(toolbar);
    spacer2->setMinimumWidth(10);
    toolbar->addWidget(spacer2);

    QLabel *resolution_selection_label = new QLabel("Resolution:",toolbar);
    resolution_selection_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    toolbar->addWidget(resolution_selection_label);

    _resolution_selection = new QComboBox(toolbar);
    _resolution_selection->setMinimumWidth(150);


    _resolution_selection->addItems(resolutionList);
    _resolution_selection->insertSeparator(resolutionList.indexOf("1536x2048 (iPad3 Portrait)")+1);
    _resolution_selection->insertSeparator(resolutionList.indexOf("240x320 (QVGA Portrait)")+1);

    connect( _resolution_selection,  combo_activated_int, this, &WorldWindow::onChangeResolution);

    toolbar->addWidget(_resolution_selection);


    //
    // Grid selection
    //

    QWidget *spacer3 = new QWidget(toolbar);
    spacer3->setMinimumWidth(10);
    toolbar->addWidget(spacer3);

    QLabel *grid_selection_label = new QLabel("Grid:",toolbar);
    grid_selection_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    toolbar->addWidget(grid_selection_label);

    _grid_visible = new QCheckBox("",toolbar);
    _grid_visible->setCheckState(Qt::Checked);
    toolbar->addWidget(_grid_visible);

    connect(	_grid_visible,  SIGNAL(stateChanged(int)),
                this,           SLOT(onChangeGrid(int))	);


    _grid_selection = new QComboBox(toolbar);
    _grid_selection->setMinimumWidth(75);

    _grid_selection->setEditable(true);

    _grid_selection->addItems({
        "None", "0.1", "0.2", "0.5", "1.0", "1.2", "1.5", "2.0", "5.0", "10.0", "20.0", "100.0",
    });
    connect(_grid_selection,  combo_activated_int, this, &WorldWindow::onChangeGrid);

    toolbar->addWidget(_grid_selection);

    //
    // Set up window
    //

    _shader = ShaderResource::import_resource(FilePath("{ED_TOOL_SHADER}"));
    ASSERT(_shader!=nullptr);
    _grid_material = MaterialResource::create();
    _grid_material->set_blend_enable(false);
    _grid_material->set_depth_enable(true);


    // Initialize builtin cameras
    for (unsigned int i = 0; i < ARRAY_SIZE(_built_in_cameras); ++i) {
        _built_in_cameras[i] = CameraObject::create();
    }

    // Front
    _built_in_cameras[0]->set_orientation( Matrix3( 1.0F,   0.0F,   0.0F,
                                                    0.0F,   1.0F,   0.0F,
                                                    0.0F,   0.0F,   1.0F    )   );

    // Back
    _built_in_cameras[1]->set_orientation( Matrix3( -1.0F,  0.0F,   0.0F,
                                                    0.0F,   1.0F,   0.0F,
                                                    0.0F,   0.0F,   -1.0F    )   );

    // Top
    _built_in_cameras[2]->set_orientation( Matrix3( 1.0F,   0.0F,   0.0F,
                                                    0.0F,   0.0F,   1.0F,
                                                    0.0F,   -1.0F,  0.0F    )   );
    // Bottom
    _built_in_cameras[3]->set_orientation( Matrix3( 1.0F,   0.0F,   0.0F,
                                                    0.0F,   0.0F,   -1.0F,
                                                    0.0F,   1.0F,   0.0F    )   );
    // Left
    _built_in_cameras[4]->set_orientation( Matrix3( 0.0F,   0.0F,   -1.0F,
                                                    0.0F,   1.0F,   0.0F,
                                                    1.0F,   0.0F,   0.0F    )   );
    // Right
    _built_in_cameras[5]->set_orientation( Matrix3( 0.0F,   0.0F,   1.0F,
                                                    0.0F,   1.0F,   0.0F,
                                                    -1.0F,   0.0F,  0.0F    )   );

    setAutoBufferSwap(false);
}

//==============================================================================
//==============================================================================

void WorldWindow::onChangeCamera(int index)
{
    CameraObject *current_camera = (CameraObject *) _camera_selection->itemData(index).value<void*>();
    _camera = checked_static_cast<CameraObject>(current_camera->shared_from_this());

    // Treat builtin cameras specially
    _built_in_camera =  (_camera == _built_in_cameras[0]) |
                        (_camera == _built_in_cameras[1]) |
                        (_camera == _built_in_cameras[2]) |
                        (_camera == _built_in_cameras[3]) |
                        (_camera == _built_in_cameras[4]) |
                        (_camera == _built_in_cameras[5]);

    if (_built_in_camera)   _builtin_camera_index = index;
    else                    _custom_camera_index = index;

    update();
}

void WorldWindow::onChangeResolution(int index)
{

    QString item_text = _resolution_selection->itemText(index);
    QStringList res = item_text.split(" ");
    QStringList res_elems = res.front().split("x");

    if (res_elems.size() != 2) {
        _desired_width = 0;
        _desired_height = 0;
    } else {
        _desired_width = res_elems.at(0).toInt();
        _desired_height = res_elems.at(1).toInt();
    }

    updateGeometry();
    update();
}

void WorldWindow::onChangeGrid (int state)
{
    update();
}

QSize WorldWindow::sizeHint (void) const
{
    return QSize(_desired_width,_desired_height);
}

//==============================================================================
//==============================================================================

void WorldWindow::refreshCameras()
{
    std::shared_ptr<World> world = _document->world();
    const std::list<std::shared_ptr<WorldNode>>& objects = world->nodes();

    _camera_selection->blockSignals(true);

    // Remember currently selected camera
    int current_camera_index = _camera_selection->currentIndex();
    int count_cameras = 0;

    CameraObject *current_camera = NULL;
    if (current_camera_index >= 0)
        current_camera = (CameraObject *) _camera_selection->itemData(current_camera_index).value<void*>();

    _camera_selection->clear();

    // Add the new cameras to the list
    for(const std::shared_ptr<WorldNode> &n : objects) {
        if ( n->isa(CameraObject::kind()) ) {
            _camera_selection->addItem( n->name().c_str(), qVariantFromValue( (void*) n.get() ) );
            ++count_cameras;
        }
    }

    // Add built in cameras
    if (count_cameras > 0)
        _camera_selection->insertSeparator(_resolution_selection->count());

    _camera_selection->addItem("Front",  qVariantFromValue( (void*) _built_in_cameras[0].get()) );
    _camera_selection->addItem("Back",  qVariantFromValue( (void*) _built_in_cameras[1].get()) );
    _camera_selection->addItem("Top",  qVariantFromValue( (void*) _built_in_cameras[2].get()) );
    _camera_selection->addItem("Bottom",  qVariantFromValue( (void*) _built_in_cameras[3].get()) );
    _camera_selection->addItem("Left",  qVariantFromValue( (void*) _built_in_cameras[4].get()) );
    _camera_selection->addItem("Right",  qVariantFromValue( (void*) _built_in_cameras[5].get()) );

    // Find the selected camera and select it again
    current_camera_index = _camera_selection->findData( qVariantFromValue( (void*) current_camera) );
    if (current_camera_index >= 0) {
        _camera_selection->setCurrentIndex(current_camera_index);
    } else if (_camera_selection->count() > 0) {
        _camera_selection->setCurrentIndex(0);
        current_camera_index = 0;
    } else {
        _camera_selection->setCurrentIndex(-2); // Just so there will be a change later on
    }

    _camera_selection->blockSignals(false);

    onChangeCamera(current_camera_index);
}

//==============================================================================
//==============================================================================

void WorldWindow::initializeGL(void)
{
    makeCurrent();
    auto v =this->context();
    qDebug() << (v!=nullptr);
    GameMainThread::show_engine(width(), height());

//    ::glEnable(GL_MULTISAMPLE);
//    GLint bufs;
//    GLint samples;
//    ::glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
//    ::glGetIntegerv(GL_SAMPLES, &samples);
//    qDebug("Have %d buffers and %d samples", bufs, samples);
}

//==============================================================================
//==============================================================================

float WorldWindow::calcScale(const std::shared_ptr<CameraObject> &camera)
{
    float scale = 1.0F;

    // Calculate a manipulator scale
    if (_tool) {

        if (camera->is_perspective()) {
            float dist = Vector3::dot(-camera->orientation().z_axis(),
                                      (_tool->getManipulatorTransform().translation() - camera->translation()));

            float one_unit_angle = std::atan(1.0F / dist);
            float camera_angle   = camera->angle() * PI / 180.0F;

            scale = camera_angle / 2.0F * 0.3F / one_unit_angle; // Approx %15 angular view
        } else {
            scale = 0.25F * _built_in_zoom;
        }
    }

    return scale;
}

//==============================================================================
//==============================================================================

void WorldWindow::drawScene(const std::shared_ptr<CameraObject> &camera, float scale)
{
    ::glPushName(0);
    _document->world()->draw(0.0F);
    ::glPopName();

    if (_tool) {
        ::glPushName(0);
        _tool->draw(_camera, scale);
        ::glPopName();
    }
}

//==============================================================================
//==============================================================================

void WorldWindow::updateBuiltInCameras(void)
{

    if (_built_in_camera) {
        float aspect = static_cast<float>(width()) / static_cast<float>(height());

        // Change positions of builtin cameras
        for (unsigned int i = 0; i < ARRAY_SIZE(_built_in_cameras); ++i) {
            _built_in_cameras[i]->set_ortho(-_built_in_zoom*aspect, _built_in_zoom*aspect, -_built_in_zoom, _built_in_zoom, -10000.0F, 10000.0F);
        }
    }

}

//==============================================================================
//==============================================================================

void WorldWindow::paintGL(void)
{
    makeCurrent();

    {
        DT3::DrawBatcher                _draw_batcher;
        updateBuiltInCameras();

        //refreshCameras();


        System::renderer()->change_display (width(), height());

        ::glClearColor( 0.15F, 0.15F, 0.15F, 0.0F );
        ::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

        if (!_camera) {
            swapBuffers();
            //doneCurrent();
            return;
        }

        // Save aspect ratio
        float save_aspect = _camera->aspect_ratio_mul();
        _camera->set_aspect_ratio_mul( static_cast<float>(width()) / static_cast<float>(height()) / System::renderer()->screen_aspect() );

        // Activate the camera
        //DrawUtils::activate_camera(_camera);

        // Replace the camera temporarily in the world
        std::shared_ptr<CameraObject> save_camera = _document->world()->camera();
        _document->world()->set_camera(_camera);

        // Draw the objects
        drawScene(_camera, calcScale(_camera));

        // Draw the selections
        for(const std::shared_ptr<PlugNode> &n : _document->selection()) {
            const std::shared_ptr<PlaceableObject> placeable = checked_cast<PlaceableObject>(n);
            if (!placeable) {
                continue;
            }

            DrawUtils::draw_selection (_draw_batcher, _camera, _grid_material, _shader, placeable->transform(), Color4b::green, placeable->radius());
        }

        if (getGridVisible()) {
            drawGrid (_draw_batcher,_camera);
        }

        _document->world()->set_camera(save_camera);

        // Set aspect ratio back to what it was
        _camera->set_aspect_ratio_mul(save_aspect);
        // drawbatcher destructor calls draw here.
    }

    swapBuffers();
    //doneCurrent();
}

void WorldWindow::pickGL(QPointF pos, EdLevelToolEvent &tool_event)
{
    makeCurrent();

    updateBuiltInCameras();

    System::renderer()->change_display (width(), height());

    if (!_camera)
        return;


    //
    // 1. Specify the array to be used for the returned hit records
    //

    GLuint buffer[1024];
    ::glSelectBuffer(ARRAY_SIZE(buffer), buffer);

    //
    // 2. Enter Selection mode
    //

    ::glRenderMode(GL_SELECT);

    //
    // 3. Initialize the name stack
    //

    ::glInitNames();

    //
    // 4. Specify the viewing volume
    //

    // Save aspect ratio
    float save_aspect = _camera->aspect_ratio_mul();
    _camera->set_aspect_ratio_mul( static_cast<float>(width()) / static_cast<float>(height()) / System::renderer()->screen_aspect() );

    // Activate the camera
    int viewport[4] = { 0, 0, width(), height() };
    _camera->set_picking(pos.x(), height() - pos.y(), 5.0F, 5.0F, viewport);

    //
    // 5. Draw the scene
    //

    // Replace the camera temporarily in the world
    std::shared_ptr<CameraObject> save_camera = _document->world()->camera();
    _document->world()->set_camera(_camera);

    float scale = calcScale(_camera);
    drawScene(_camera, scale);

    _document->world()->set_camera(save_camera);


    //
    // 6. Exit selection mode
    //

    _camera->end_picking();
    _camera->calculate_frustum();    // Force refresh of internal matrices


    GLint hits = ::glRenderMode(GL_RENDER);

    //
    // 7. Build Hit event
    //

    // Build a ray used for mouse interactions
    float x = static_cast<float>(pos.x()) / static_cast<float>(width()) * 2.0F - 1.0F;                  // -1.0 to 1.0
    float y = static_cast<float>(height() - pos.y()) / static_cast<float>(height()) * 2.0F - 1.0F;  // -1.0 to 1.0

    tool_event._camera = _camera;
    tool_event._ray_src = _camera->unproject_point( Vector3(x,y,-1.0F) );
    tool_event._ray_dest = _camera->unproject_point( Vector3(x,y,1.0F) );
    tool_event._control_id = 0;

    std::cout << x << " " << y << std::endl;
    std::cout << "src:  " << tool_event._ray_src.x << " " << tool_event._ray_src.y << " " << tool_event._ray_src.z << std::endl;
    std::cout << "dest: " << tool_event._ray_dest.x << " " << tool_event._ray_dest.y << " " << tool_event._ray_dest.z << std::endl;

    //
    // 8. Report hits
    //

    GLuint *ptr = buffer;

    float selection_z = std::numeric_limits<float>::infinity();
    std::shared_ptr<WorldNode> selection;
    bool using_tool = false;

    for (int i = 0; i < hits; ++i) {
        GLuint num_ids = *ptr;  ++ptr;
        float zmin = (float) ((double) (*ptr) / 0x7FFFFFFF);	++ptr;
        float zmax = (float) ((double) (*ptr) / 0x7FFFFFFF);	++ptr;

        LOG_MESSAGE << "zmin :" << zmin << "  " << "zmax: " << zmax;

        // Check for tool selection
        if (num_ids == 2) {
            /*GLuint id1 = *ptr;*/ ++ptr;
            GLuint id2 = *ptr; ++ptr;

            tool_event._control_id = id2;
            using_tool = true;

        // Check for object selection
        } else if (num_ids == 1) {
            GLuint id1 = *ptr; ++ptr;

            if (tool_event._event_type == EdLevelToolEvent::MOUSE_DOWN && ((zmin + zmax) * 0.5f) < selection_z) {
                // Change the selection
                selection = _document->world()->node_by_id(id1);
            }

        }

    }

    //
    // 9. Handle event
    //

    if (tool_event._event_type == EdLevelToolEvent::MOUSE_DOWN) {

        if ( (using_tool && _tool) ) {
            _tool->doEvent(tool_event);
        } else if (selection) {
            std::list<std::shared_ptr<PlugNode>> selection_list;
            selection_list.push_back(selection);
            emit doSelectionChanged(selection_list);
        }

    } else {

        if (_tool) {
            _tool->doEvent(tool_event);
        }

    }



    // Set aspect ratio back to what it was
    _camera->set_aspect_ratio_mul(save_aspect);
    _camera->calculate_frustum();    // Force refresh of internal matrices

    doneCurrent();
}

//==============================================================================
//==============================================================================

void WorldWindow::resizeGL( int w, int h )
{
    ::glViewport(0, 0, w, h);
}

//==============================================================================
//==============================================================================

void WorldWindow::onSelectComponent (void)
{
    QAction *action = qobject_cast<QAction*>(sender());

    LOG_MESSAGE << "Creating tool: " << action->data().toString().toUtf8().data();
    QString classname = action->data().toString();
    std::shared_ptr<EdLevelTool> tool(EditorObjectFactory::createObjectT<EdLevelTool>(classname));
    if(_tool)
        disconnect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);

    _tool = tool;

    if (_tool) {
        _tool->setSelection(_document->selection());
        connect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);
    }

    update();
}

QAction *WorldWindow::addContextMenuFromMetaObject(QMenu *context_menu,const QMetaObject *toolclassprops) {
    QString toolname=toolNameFromMetaObject(toolclassprops);
    Q_ASSERT(!toolname.isEmpty());

    QAction *component = new QAction(this);
    component->setText(toolname);
    component->setVisible(true);
    component->setData(toolclassprops->className());

    connect(component, &QAction::triggered, this, &WorldWindow::onSelectComponent);
    context_menu->addAction(component);
    return component;
}
//==============================================================================
//==============================================================================

void WorldWindow::toolContextMenu(QMouseEvent *event)
{
    // Add Components
    const std::list<std::shared_ptr<PlugNode>> &selection = _document->selection();
    if (selection.size() != 1)
        return;

    std::shared_ptr<PlugNode> front          = selection.front();
    bool                      is_object_base = front->isa(ObjectBase::kind());
    bool                      is_placeable   = front->isa(PlaceableObject::kind());

    // Context Menu
    QMenu *context_menu = new QMenu();

    // Pan
    QAction *pan_action = addContextMenuFromMetaObject(context_menu, &EdLevelManipPan::staticMetaObject);
    pan_action->setEnabled(is_placeable);

    // Rotate

    QAction *rotate_action = addContextMenuFromMetaObject(context_menu, &EdLevelManipRotate::staticMetaObject);
    rotate_action->setEnabled(is_placeable);

    // Scale
    QAction *scale_action = addContextMenuFromMetaObject(context_menu, &EdLevelManipScale::staticMetaObject);
    scale_action->setEnabled(is_placeable);

    // Separator
    context_menu->addSeparator();

    // Base Class
    const char *class_id     = front->class_id_child();
    for (const QMetaObject *toolclassprops : EngineObjectTools::toolsForEngineClass(class_id)) {
        addContextMenuFromMetaObject(context_menu, toolclassprops);
    }

    if (is_object_base) {
        std::shared_ptr<ObjectBase> base = checked_static_cast<ObjectBase>(front);

        // Sub component menu items
        for (std::shared_ptr<ComponentBase> &n : base->all_components()) {

            char *class_id     = n->class_id_child();
            for (const QMetaObject *toolclassprops : EngineObjectTools::toolsForEngineClass(class_id)) {
                addContextMenuFromMetaObject(context_menu, toolclassprops);
            }
        }
    }

    context_menu->exec(event->globalPos());
}

//==============================================================================
//==============================================================================

bool WorldWindow::getGridVisible (void)
{
    return (_grid_visible->checkState() == Qt::Checked);
}

float WorldWindow::getGrid(void)
{
    bool ok;
    float grid = _grid_selection->currentText().toFloat(&ok);

    if (!ok)    return 0.0F;
    else        return grid;
}

//==============================================================================
//==============================================================================

void WorldWindow::mousePressEvent(QMouseEvent *event)
{
    emit doUndoBlock();

    update();

    if (event->buttons() == Qt::RightButton && !(event->modifiers() & Qt::ALT)) {

        toolContextMenu(event);

    } else {
        _last_position = event->pos();

        if (!(event->modifiers() & Qt::ALT)) {
            // Do picking
            EdLevelToolEvent tool_event;
            tool_event._event_type = EdLevelToolEvent::MOUSE_DOWN;
            tool_event._mouse_x = event->pos().x();
            tool_event._mouse_y = event->pos().y();
            tool_event._window_width = width();
            tool_event._window_height = height();
            tool_event._grid = getGrid();
            tool_event._modifiers = (event->modifiers() & Qt::ALT ? EdLevelToolEvent::MODIFIER_OPTION_ALT : 0) |
                                    (event->modifiers() & Qt::CTRL ? EdLevelToolEvent::MODIFIER_CONTROL : 0) |
                                    (event->modifiers() & Qt::SHIFT ? EdLevelToolEvent::MODIFIER_SHIFT : 0) |
                                    (event->modifiers() & Qt::META ? EdLevelToolEvent::MODIFIER_META : 0);

            pickGL(event->pos(), tool_event);
        }
        update();
    }
}

void WorldWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPointF delta = event->pos() - _last_position;
    _last_position = event->pos();

    bool pan = (event->buttons() == Qt::MidButton) || ( (event->buttons() == Qt::LeftButton) && (event->modifiers() & Qt::ALT) && (event->modifiers() & Qt::SHIFT) );
    bool rot = (event->buttons() == Qt::RightButton) && (event->modifiers() & Qt::ALT) && !_built_in_camera;
    bool zoom = (event->buttons() == Qt::LeftButton) && (event->modifiers() & Qt::ALT);

    if (_camera && (pan || rot || zoom) ) {
        Vector3 position = _camera->translation();
        Matrix3 orientation = _camera->orientation();

        if (pan) {
            position = position - orientation.y_axis() * delta.y() + orientation.x_axis() * delta.x();

        } else if (rot) {

            Matrix3 roty, rotx;
            roty = Matrix3::set_rotation_y(delta.x() * 0.01F);
            rotx = Matrix3::set_rotation_x(delta.y() * 0.01F);

            orientation = (roty * orientation * rotx).orthoed();

        } else if (zoom) {

            if (_built_in_camera) {
                _built_in_zoom += delta.y();

                if (_built_in_zoom < 1.0F)          _built_in_zoom = 1.0F;
                else if (_built_in_zoom > 10000.0F)  _built_in_zoom = 10000.0F;

            } else {

                Matrix3 roty;
                roty = Matrix3::set_rotation_y(delta.x() * 0.01F);

                Vector3 straight_z(orientation.z_axis());
                straight_z.y = 0.0F;
                straight_z.normalize();

                orientation = (roty * orientation).orthoed();
                position = position + straight_z * delta.y();
            }
        }


        if (_built_in_camera) {

            // Change positions of builtin cameras
            for (unsigned int i = 0; i < ARRAY_SIZE(_built_in_cameras); ++i) {

                // Set the transform of the camera
                Matrix4 transform = _built_in_cameras[i]->transform();
                transform.set_translation(position);
                _built_in_cameras[i]->set_transform(transform);

            }

            update();

        } else {
            // Set the transform of the camera
            Matrix4 transform = Matrix4::identity();
            transform.set_translation(position);
            transform.set_orientation(orientation);

            TextBufferStream stream;
            stream << transform;
            emit doCommand(QString("SetTransform ") + _camera->full_name().c_str() + " (" + stream.buffer().c_str() + ")");
        }

    } else {
        // Do picking
        EdLevelToolEvent tool_event;
        tool_event._event_type = EdLevelToolEvent::MOUSE_DRAG;
        tool_event._mouse_x = event->pos().x();
        tool_event._mouse_y = event->pos().y();
        tool_event._window_width = width();
        tool_event._window_height = height();
        tool_event._grid = getGrid();
        tool_event._modifiers = (event->modifiers() & Qt::ALT ? EdLevelToolEvent::MODIFIER_OPTION_ALT : 0) |
                                (event->modifiers() & Qt::CTRL ? EdLevelToolEvent::MODIFIER_CONTROL : 0) |
                                (event->modifiers() & Qt::SHIFT ? EdLevelToolEvent::MODIFIER_SHIFT : 0) |
                                (event->modifiers() & Qt::META ? EdLevelToolEvent::MODIFIER_META : 0);

        pickGL(event->pos(), tool_event);
        update();
    }

}

void WorldWindow::mouseReleaseEvent	(QMouseEvent *event)
{
    // Do picking
    EdLevelToolEvent tool_event;
    tool_event._event_type = EdLevelToolEvent::MOUSE_UP;
    tool_event._mouse_x = event->pos().x();
    tool_event._mouse_y = event->pos().y();
    tool_event._window_width = width();
    tool_event._window_height = height();
    tool_event._grid = getGrid();
    tool_event._modifiers = (event->modifiers() & Qt::ALT ? EdLevelToolEvent::MODIFIER_OPTION_ALT : 0) |
                            (event->modifiers() & Qt::CTRL ? EdLevelToolEvent::MODIFIER_CONTROL : 0) |
                            (event->modifiers() & Qt::SHIFT ? EdLevelToolEvent::MODIFIER_SHIFT : 0) |
                            (event->modifiers() & Qt::META ? EdLevelToolEvent::MODIFIER_META : 0);

    pickGL(event->pos(), tool_event);
    update();
}

//==============================================================================
//==============================================================================

void WorldWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    bool is_builtin_tool = _tool && ((qobject_cast<EdLevelManipPan *>(_tool.get())!=nullptr) ||
                                     (qobject_cast<EdLevelManipRotate *>(_tool.get())) ||
                                     (qobject_cast<EdLevelManipScale *>(_tool.get())));

    if (key == Qt::Key_Q) {
        onArrowTool();
        event->accept();
    } else if (key == Qt::Key_W) {
        onPanTool();
        event->accept();
    } else if (key == Qt::Key_E) {
        onRotateTool();
        event->accept();
    } else if (key == Qt::Key_R) {
        onScaleTool();
        event->accept();
    } else if ((event->matches(QKeySequence::Delete) || key == 0x1000003) && (!_tool || is_builtin_tool)) {

        for (const std::shared_ptr<PlugNode> &n : _document->selection()) {
            std::shared_ptr<WorldNode> node = checked_cast<WorldNode>(n);
            if (node) {
                emit doCommand(QString("Remove \"%1\"").arg(node->name().c_str()));
            }
        }

    } else if (key == Qt::Key_Space) {

        // Swap cameras
        if (_camera_selection->currentIndex() == _builtin_camera_index) {

            if (_custom_camera_index >= 0 && _custom_camera_index < _camera_selection->count() &&
                _camera_selection->itemData(_custom_camera_index).value<void *>()) {
                _camera_selection->setCurrentIndex(_custom_camera_index);
                onChangeCamera(_custom_camera_index);
            }

        } else {

            if (_builtin_camera_index >= 0 && _builtin_camera_index < _camera_selection->count() &&
                _camera_selection->itemData(_builtin_camera_index).value<void *>()) {
                _camera_selection->setCurrentIndex(_builtin_camera_index);
                onChangeCamera(_builtin_camera_index);
            }
        }

        event->accept();
    } else {
        EdLevelToolEvent tool_event;
        tool_event._event_type = EdLevelToolEvent::KEY_DOWN;
        tool_event._key_code   = key;
        tool_event._grid       = getGrid();
        tool_event._camera     = _camera;
        tool_event._modifiers  = (event->modifiers() & Qt::ALT ? EdLevelToolEvent::MODIFIER_OPTION_ALT : 0) |
                                (event->modifiers() & Qt::CTRL ? EdLevelToolEvent::MODIFIER_CONTROL : 0) |
                                (event->modifiers() & Qt::SHIFT ? EdLevelToolEvent::MODIFIER_SHIFT : 0) |
                                (event->modifiers() & Qt::META ? EdLevelToolEvent::MODIFIER_META : 0);

        if (_tool) {
            _tool->doEvent(tool_event);
        }
        update();
    }
}

//==============================================================================
//==============================================================================

void WorldWindow::drawGrid (DT3::DrawBatcher &draw_batch,const std::shared_ptr<CameraObject> &camera)
{
    float grid = getGrid();
    if (grid <= 0.0F)
        grid = 1.0F;

    const int SIZE = 100;
    ASSERT(_shader!=nullptr);
    draw_batch.batch_begin(camera, _grid_material, _shader, Matrix4::identity(), DT3GL_PRIM_LINES, DrawBatcher::FMT_V | DrawBatcher::FMT_C);

    // Minor lines
    for (int p = -SIZE; p <= SIZE; ++p) {
        if (p == 0) continue;

        if ( (p%10) != 0) {
            draw_batch.add().v(p * grid, 0.0F, -SIZE * grid).c(Color4b::grey25);
            draw_batch.add().v(p * grid, 0.0F, +SIZE * grid).c(Color4b::grey25);
            draw_batch.add().v(-SIZE * grid, 0.0F, p * grid).c(Color4b::grey25);
            draw_batch.add().v(+SIZE * grid, 0.0F, p * grid).c(Color4b::grey25);
        }

        draw_batch.batch_split();
    }

    // Major lines
    for (int p = -SIZE; p <= SIZE; ++p) {
        if (p == 0)
            continue;

        if ( (p%10) == 0) {
            draw_batch.add().v(p * grid, 0.0F, -SIZE * grid).c(Color4b::grey50);
            draw_batch.add().v(p * grid, 0.0F, +SIZE * grid).c(Color4b::grey50);
            draw_batch.add().v(-SIZE * grid, 0.0F, p * grid).c(Color4b::grey50);
            draw_batch.add().v(+SIZE * grid, 0.0F, p * grid).c(Color4b::grey50);
        }

        draw_batch.batch_split();
    }



    draw_batch.add().v(-SIZE * grid, 0.0F, 0.0F).c(Color4b::red);
    draw_batch.add().v(SIZE * grid, 0.0F, 0.0F).c(Color4b::red);

    draw_batch.batch_split();

    draw_batch.add().v(0.0F, 0.0F, -SIZE * grid).c(Color4b::blue);
    draw_batch.add().v(0.0F, 0.0F, SIZE * grid).c(Color4b::blue);

    draw_batch.batch_split();

    draw_batch.batch_end();
}

//==============================================================================
//==============================================================================

void WorldWindow::onArrowTool(void)
{
    _tool.reset();

    const std::list<std::shared_ptr<PlugNode>> &selection = _document->selection();

    // Check that all objects are the same type
    if (!selection.empty()) {

        char *class_id = selection.front()->class_id_child();
        // TODO: build a common subset of tools that exist for all selected objects
        for (const std::shared_ptr<PlugNode> &n : _document->selection()) {

            if (n->class_id_child() != class_id)
                return; // Different so no further action needed
        }

        if(_tool)
            disconnect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);
        // find tools for selected class_id
        static QVector<const QMetaObject *> &tools_for_selection(EngineObjectTools::toolsForEngineClass(class_id));
        if(tools_for_selection.size()==1) { //TODO: currently only single tool classes supported for arrowtool
            // take the first tool from the available set.
            _tool = std::shared_ptr<EdLevelTool>(EditorObjectFactory::createObjectT<EdLevelTool>(tools_for_selection.first()->className()));
            if (_tool) {
                _tool->setSelection(selection);
                connect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);
            }
        }
    }

    update();
}

void WorldWindow::onPanTool (void)
{
    if(_tool)
        disconnect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);
    _tool = std::make_shared<EdLevelManipPan>();

    const std::list<std::shared_ptr<PlugNode>>& selection = _document->selection();
    _tool->setSelection(selection);
    connect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);

    update();
}

void WorldWindow::onRotateTool (void)
{
    if(_tool)
        disconnect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);
    _tool = std::make_shared<EdLevelManipRotate>();

    const std::list<std::shared_ptr<PlugNode>>& selection = _document->selection();
    _tool->setSelection(selection);
    connect(_tool.get(),&EdLevelTool::doCommand,this,&WorldWindow::doCommand);

    update();
}

void WorldWindow::onScaleTool (void)
{
    _tool = std::make_shared<EdLevelManipScale>();

    const std::list<std::shared_ptr<PlugNode>>& selection = _document->selection();
    _tool->setSelection(selection);

    update();
}

//==============================================================================
//==============================================================================

void WorldWindow::onRefreshWorld (void)
{
    refreshCameras();
    update();
}

void WorldWindow::onSelectionChanged (const std::list<std::shared_ptr<PlugNode>> &selection_list)
{
    if (_tool) {
        _tool->setSelection(selection_list);
    }

    update();
}

void WorldWindow::changeEvent(QEvent *e)
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
