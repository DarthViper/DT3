//==============================================================================
///
///	File: EdSpriteAppMain.cpp
///
/// Copyright (C) 2000-2013 by Smells Like Donkey, Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "EdSpriteAppMain.hpp"
#include "EdSpriteMainWindow.hpp"

#include <QtWidgets/QApplication>
#include <QtCore/QFile>
#include <QtWidgets/QLabel>

#include "DT3Core/System/System.hpp"
#include "DT3Core/Entry/GameMainThread.hpp"

#include "DT3Core/System/Application.hpp"
#include "DT3Core/System/StaticInitializer.hpp"
#include "DT3Core/System/Configure.hpp"

#include "DT3Core/Devices/DeviceGraphics.hpp"
#include "DT3Core/Devices/DeviceAudio.hpp"
#include "DT3Core/Devices/DeviceInput.hpp"
#include "DT3Core/Devices/DeviceNetwork.hpp"
//#include "ResourceManager.hpp"
#include "DT3Core/Types/Utility/ConsoleStream.hpp"
//#include "Profiler.hpp"
//#include "DeviceNetwork.hpp"
//#include "DeviceReplication.hpp"
//#include "FileManager.hpp"

#include "DT3Core/Resources/ResourceTypes/MaterialResource.hpp"
//#include "CheckedCast.hpp"
#include "DT3Core/System/Factory.hpp"

using namespace DT3;

//==============================================================================
//==============================================================================

int main (int argc, char *argv[])
{
    StaticInitializer::initialize();

    // Import a config file for the engine
    Configure::import_config(FilePath("{config_engine.txt}"));

    //
    // Create Managers
    //

    LOG_MESSAGE << "Creating Input Manager...";
    std::shared_ptr<DeviceInput> input_manager = checked_cast<DeviceInput>(Factory::create_object("{CLASS_INPUT_DEVICE}"));
    if (input_manager)      System::set_input_manager(input_manager);
    else                    System::set_input_manager(DeviceInput::create());       // Default NULL device
    LOG_MESSAGE << " Created " << System::input_manager()->class_id_child();

//    LOG_MESSAGE << "Creating Music Device...";
//    std::shared_ptr<DeviceMusic> music_device = checked_cast<DeviceMusic>(Factory::create_object("{CLASS_MUSIC_DEVICE}"));
//    if (music_device)       System::set_music_renderer(music_device);
//    else                    System::set_music_renderer(DeviceMusic::create());      // Default NULL device
//    LOG_MESSAGE << " Created " << System::music_renderer()->class_id_child();

    LOG_MESSAGE << "Creating Audio Device...";
    std::shared_ptr<DeviceAudio> audio_device = checked_cast<DeviceAudio>(Factory::create_object("{CLASS_AUDIO_DEVICE}"));
    if (audio_device)       System::set_audio_renderer(audio_device);
    else                    System::set_audio_renderer(DeviceAudio::create());      // Default NULL device
    LOG_MESSAGE << " Created " << System::audio_renderer()->class_id_child();


//    LOG_MESSAGE << "Creating Resource Manager...";
//    ResourceManager		*resource_manager = checkedCast<ResourceManager *>(Factory::createObject("{CLASS_RESOURCE_MANAGER}"));
//    System::setResourceManager(resource_manager);
//    RELEASE(resource_manager);

    LOG_MESSAGE << "Creating Network Manager...";
    std::shared_ptr<DeviceNetwork> network_manager = checked_cast<DeviceNetwork>(Factory::create_object("{CLASS_NETWORK_DEVICE}"));
    if (network_manager)    System::set_network_manager(network_manager);
    else                    System::set_network_manager(DeviceNetwork::create());   // Default NULL device
    LOG_MESSAGE << " Created " << System::network_manager()->class_id_child();

//    LOG_MESSAGE << "Creating Replication Manager...";
//    DeviceReplication	*replication_manager = checkedCast<DeviceReplication *>(Factory::createObject("{CLASS_REPLICATION_MANAGER}"));
//    System::setReplicationManager(replication_manager);
//    RELEASE(replication_manager);

    //
    // Application object
    //

    // Build the application class
    LOG_MESSAGE << "Creating Application...";
    std::shared_ptr<Application> application = checked_cast<Application>(Factory::create_object("{CLASS_APPLICATION}"));
    if (application)        System::set_application(application);
    else                    System::set_application(Application::create());      // Default NULL device
    LOG_MESSAGE << " Created " << System::application()->class_id_child();


    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QApplication::setStyle("fusion");

    // Set style sheet
    QFile file(":/PropertyList.qss");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString style_sheet = file.readAll();
    file.close();

    QApplication app(argc, argv);
    app.setStyleSheet(style_sheet);

    EdSpriteMainWindow *window = new EdSpriteMainWindow();
    window->show();

    QObject::connect(	&app,       SIGNAL(focusChanged(QWidget*,QWidget*)),
                        window,     SLOT(onAppFocusChanged(QWidget*,QWidget*))	);


    app.exec();
    GameMainThread::destroy_engine();
    //
    // Destroy Managers
    //

    StaticInitializer::destroy();
}

//==============================================================================
//==============================================================================

