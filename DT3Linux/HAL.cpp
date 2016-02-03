//==============================================================================
///
///	File: HAL.cpp
///
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///
//==============================================================================

#include "DT3Linux/HAL.hpp"
#include "DT3Core/System/StaticInitializer.hpp"
#include "DT3Core/Types/FileBuffer/FilePath.hpp"
#include "DT3Core/Types/Utility/DisplayMode.hpp"
#include "DT3Core/Types/Utility/Error.hpp"
#include "DT3Core/Types/Utility/MoreStrings.hpp"
#include "DT3Core/Types/Utility/Assert.hpp"
#include "DT3Core/Types/Network/URL.hpp"
#include "DT3Core/System/Globals.hpp"

#include <QtCore/QProcess>
#include <QtCore/QUrl>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
#include <QtGui/QDesktopServices>

#include <iostream>
#include <algorithm>
#include <thread>
#include <sys/stat.h>
#include <dirent.h>
#include <chrono>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <QDir>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
//==============================================================================

GLOBAL_STATIC_INITIALIZATION(0,HAL::initialize())
GLOBAL_STATIC_DESTRUCTION(0,HAL::destroy())

//==============================================================================
//==============================================================================

#if DT3_OS == DT3_MACOSX
    // Restore state for displays
    const int32_t         MAX_DISPLAYS = 32;
    CGDisplayModeRef    g_display_restore_state[MAX_DISPLAYS];
#endif

//==============================================================================
//==============================================================================

void HAL::initialize (void)
{
#if DT3_OS == DT3_IOS
    //
    // iPhone specific audio session initialization
    //

    // Allow background music
    NSError *setCategoryErr = nil;
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryAmbient error:&setCategoryErr];

    [AVAudioSession sharedInstance];
    [[AVAudioSession sharedInstance] setActive:YES error:NULL];



//	// Just set these to NULL if you don't want a callback function
//    ::AudioSessionInitialize (NULL,NULL,NULL,NULL);
//
//    // Set audio category
//    UInt32 sessionCategory = kAudioSessionCategory_SoloAmbientSound;
//    ::AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
//    ::AudioSessionSetActive(true);
#endif

#if DT3_OS == DT3_MACOSX
    CGDirectDisplayID display_array[MAX_DISPLAYS];
    CGDisplayCount num_displays;
    CGGetActiveDisplayList (MAX_DISPLAYS, display_array, &num_displays);

    // Restore any display states that have been changed
    for (CGDisplayCount i = 0; i < num_displays; ++i) {
        g_display_restore_state[i] = ::CGDisplayCopyDisplayMode(display_array[i]);
    }

#endif
}

void HAL::destroy (void)
{
#if DT3_OS == DT3_MACOSX

    CGDirectDisplayID display_array[MAX_DISPLAYS];
    CGDisplayCount numDisplays;
    CGGetActiveDisplayList (MAX_DISPLAYS, display_array, &numDisplays);

    // Restore any display states that have been changed
    for (CGDisplayCount i = 0; i < numDisplays; ++i) {

        ::CGDisplaySetDisplayMode (display_array[i], g_display_restore_state[i], NULL);
        ::CGDisplayModeRelease(g_display_restore_state[i]);

        if (CGDisplayIsCaptured(display_array[i]))
            ::CGDisplayRelease(display_array[i]);
    }

#endif
}

//==============================================================================
//==============================================================================

void HAL::log (const std::string &message)
{
    std::cout << message << std::endl;
}

//==============================================================================
//==============================================================================

DTdouble HAL::program_running_time(void)
{
    static auto start_time = std::chrono::high_resolution_clock::now();
    auto new_time = std::chrono::high_resolution_clock::now();

    typedef std::chrono::milliseconds ms;
    ms running_time = std::chrono::duration_cast<ms>(new_time - start_time);

    return DTdouble(running_time.count());
}

//==============================================================================
//==============================================================================

void HAL::run_on_command_line (const std::string &command, const std::vector<std::string> &args)
{
    QStringList qt_args;
    for(const std::string &s : args)
        qt_args.push_back(QString::fromStdString(s));
    if(0!=QProcess::execute(QString::fromStdString(command),qt_args)) {
        ERRORMSG("Unable to start Game");
    }
}

//==============================================================================
//==============================================================================
# if 0
void HAL::display_modes (std::map<int32_t, std::vector<DisplayMode>> &modes)
{
    modes.clear();

#if DT3_OS == DT3_MACOSX

    // see http://www.carbondev.com/site/?page=CGDisplaymode_list

    CGDirectDisplayID display_array[MAX_DISPLAYS];
    CGDisplayCount numDisplays;
    CGGetActiveDisplayList (MAX_DISPLAYS, display_array, &numDisplays);


    for(uint32_t i = 0; i < numDisplays; i++) {

        // get a list of display modes for the display
        CFArrayRef mode_list = ::CGDisplayCopyAllDisplayModes(display_array[i],NULL);
        CFIndex count = ::CFArrayGetCount(mode_list);

        std::vector<DisplayMode> modes_for_display;

        for(uint32_t j = 0; j < count; j++) {

            // look at each mode in the available list
            CGDisplayModeRef cg_mode = (CGDisplayModeRef)CFArrayGetValueAtIndex(mode_list, j);

            //CFBooleanRef stretched = (CFBooleanRef) CFDictionaryGetValue(mode, kCGDisplayModeIsStretched);
            //if (!stretched || !CFBooleanGetValue(stretched))	continue;

            //CFNumberRef bitsPerPixel = (CFNumberRef)CFDictionaryGetValue(mode, kCGDisplayBitsPerPixel);
            int32_t width = static_cast<int32_t>(::CGDisplayModeGetWidth(cg_mode));
            int32_t height = static_cast<int32_t>(::CGDisplayModeGetHeight(cg_mode));
            DTdouble refresh = static_cast<DTdouble>(::CGDisplayModeGetRefreshRate(cg_mode));

            CFStringRef pixelEncoding = ::CGDisplayModeCopyPixelEncoding(cg_mode);

            // Allow only 32-bit
            if (CFStringCompare(pixelEncoding,CFSTR(IO32BitDirectPixels),0) == kCFCompareEqualTo) {
                CFRelease(pixelEncoding);
            } else {
                CFRelease(pixelEncoding);
                continue;
            }

            DisplayMode m;
            m.set_width(width);
            m.set_height(height);
            m.set_refresh_rate(refresh);

            if ( std::find(modes_for_display.begin(), modes_for_display.end(), m) == modes_for_display.end()) {
                modes_for_display.push_back(m);
            }

        }

        std::sort(modes_for_display.begin(), modes_for_display.end());

        modes[i] = modes_for_display;

        CFRelease(mode_list);
    }
#endif

}

void HAL::switch_display_mode (int32_t display, DisplayMode mode)
{

#if DT3_OS == DT3_MACOSX

    CGDirectDisplayID display_array[MAX_DISPLAYS];
    CGDisplayCount numDisplays;
    CGGetActiveDisplayList (MAX_DISPLAYS, display_array, &numDisplays);

    // Get the mode again
    CGDisplayModeRef cg_mode;
    CFIndex index, count;
    CFArrayRef mode_list;

    mode_list = ::CGDisplayCopyAllDisplayModes (display_array[display], NULL);
    count = ::CFArrayGetCount (mode_list);

    for (index = 0; index < count; index++) {

        cg_mode = (CGDisplayModeRef)CFArrayGetValueAtIndex (mode_list, index);

        int32_t width = (int32_t) ::CGDisplayModeGetWidth(cg_mode);
        int32_t height = (int32_t) ::CGDisplayModeGetHeight(cg_mode);
        CFStringRef pixelEncoding = ::CGDisplayModeCopyPixelEncoding(cg_mode);

        if (height == mode.height() && width == mode.width() && CFStringCompare(pixelEncoding,CFSTR(IO32BitDirectPixels),0) == kCFCompareEqualTo) {
            CFRelease(pixelEncoding);
        } else {
            CFRelease(pixelEncoding);
            continue;
        }

        // Time to capture the display
        if (!::CGDisplayIsCaptured(display_array[display])) {
            ::CGDisplayCapture(display_array[display]);
        }

        ::CGDisplaySetDisplayMode (display_array[display], cg_mode, NULL);

    }
    CFRelease(mode_list);

#endif

}
void HAL::display_rect (int32_t display, int32_t &x, int32_t &y, int32_t &width, int32_t &height)
{
#if DT3_OS == DT3_MACOSX

    CGDirectDisplayID display_array[MAX_DISPLAYS];
    CGDisplayCount numDisplays;
    ::CGGetActiveDisplayList (MAX_DISPLAYS, display_array, &numDisplays);

    CGRect r = ::CGDisplayBounds (display_array[display]);
    x = static_cast<int32_t>(r.origin.x);
    y = static_cast<int32_t>(r.origin.y);
    width = static_cast<int32_t>(r.size.width);
    height = static_cast<int32_t>(r.size.height);

#endif
}

#endif
//==============================================================================
//==============================================================================

void HAL::launch_browser (const URL &url)
{
    QDesktopServices::openUrl(QUrl(url.full_url().c_str(), QUrl::TolerantMode));
}

//==============================================================================
//==============================================================================

void HAL::launch_editor (const FilePath &path)
{
    QDesktopServices::openUrl(QUrl(QStringLiteral("file::///")+path.full_path().c_str(), QUrl::TolerantMode));
}

//==============================================================================
//==============================================================================

uint32_t HAL::num_CPU_cores (void)
{
    return std::thread::hardware_concurrency();
}

//==============================================================================
//==============================================================================

bool HAL::move_file (const FilePath &from, const FilePath &to)
{
    if (link(from.full_path().c_str(), to.full_path().c_str()) == -1)
        return false;

    if (unlink(from.full_path().c_str()) == -1)
        return false;

    return true;
}

bool HAL::delete_file (const FilePath &file)
{

    if (unlink(file.full_path().c_str()) == -1)
        return false;

    return true;
}

uint64_t HAL::modification_date (const FilePath &file)
{
    struct stat buffer;
    if (stat(file.full_path().c_str(), &buffer))
        return 0;

    return static_cast<uint32_t>(buffer.st_mtime);
}

bool HAL::is_dir (const FilePath &file)
{
    struct stat buffer;
    if (stat(file.full_path().c_str(), &buffer))
        return 0;

    return (bool) S_ISDIR(buffer.st_mode);
}

std::string HAL::path_separator (void)
{
    return "/";
}

void HAL::list_directory (const FilePath &pathname, bool recursive, std::vector<FilePath> &paths)
{
    // set up and run platform specific iteration routines

    // Prime the queue
    std::list<std::string> dir_queue;
    dir_queue.push_back(pathname.full_path());

    while (dir_queue.size()) {
        std::string dir = dir_queue.back();
        dir_queue.pop_back();

        // Build the name list
        const QDir curdir(dir.c_str());
        for(const QFileInfo &fi : curdir.entryInfoList()) {
            // Skip invisible files
            if(fi.fileName().startsWith('.'))
                continue;
            if(fi.isDir()) {
                std::string entry = dir + "/" + fi.fileName().toStdString();

                paths.push_back(FilePath(entry));

                if (recursive) {
                    dir_queue.push_back(entry);
                }
            }
            else if(fi.isFile()) {
                std::string entry = dir + "/" + fi.fileName().toStdString();
                paths.push_back(FilePath(entry));
            }
        }

    }

}


FilePath HAL::app_dir (void)
{
    FilePath result;
    char buffer[256];
    ssize_t r;

    r = readlink("/proc/self/exe",buffer,sizeof(buffer));

    if(r == -1){
        result = FilePath(".");
        //ASSERT(r == -1);
    }else{
        std::string path_to_app  = std::string(buffer);
        result = FilePath(FilePath::dir_from_path(path_to_app));
    }

    return result;



#if DT3_OS == DT3_MACOSX
    // get Current directory
    DTcharacter cstr[1024];	//MAXPATHLEN??

    // get Application path
    CFURLRef mainURL = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFURLRef tempURL = CFURLCreateCopyDeletingLastPathComponent(NULL, mainURL);
    CFStringRef text = CFURLCopyFileSystemPath( tempURL, kCFURLPOSIXPathStyle );

    if (CFStringGetCString( text, cstr, sizeof(cstr), kCFStringEncodingUTF8 )) {

        std::string path(cstr);

        // TODO: Fix me.
        if (path.find("/Debug") != std::string::npos ||
            path.find("/Release") != std::string::npos) {
            path = path.substr(0, path.find_last_of('/'));
        }

        result = FilePath(path);
    }

    CFRelease(text);
    CFRelease(mainURL);
    CFRelease(tempURL);

#elif DT3_OS == DT3_IOS
    // get Current directory
    DTcharacter cstr[1024];	//MAXPATHLEN??

    // get Application path
    CFURLRef mainURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFStringRef text = CFURLCopyFileSystemPath( mainURL, kCFURLPOSIXPathStyle );

    if (CFStringGetCString( text, cstr, sizeof(cstr), kCFStringEncodingUTF8 )) {
        result = FilePath(cstr);
    }

    CFRelease(text);
    CFRelease(mainURL);
#endif

}


FilePath HAL::save_dir (void)
{
    FilePath result;

    //
    // Determine save Files Dir
    //
    char* home_path = getenv("HOME");
    std::string hpath = std::string(home_path);


    if(home_path){
        result = FilePath(hpath+"/Documents");
    }else{
        result = app_dir();
    }

    return result;

#if DT3_OS == DT3_MACOSX
    FSRef prefs_dir_ref;
    OSErr err = FSFindFolder (kUserDomain,kPreferencesFolderType,false,&prefs_dir_ref);
    if (err == noErr) {
        DTcharacter cstr[1024];	//MAXPATHLEN??
        CFStringRef text;

        CFURLRef prefsURL = CFURLCreateFromFSRef (kCFAllocatorDefault, &prefs_dir_ref);
        text = CFURLCopyFileSystemPath( prefsURL, kCFURLPOSIXPathStyle );

        if (CFStringGetCString( text, cstr, sizeof(cstr), kCFStringEncodingUTF8 )) {
            result = FilePath(cstr);
        }

        CFRelease(text);
        CFRelease(prefsURL);
    }
#elif DT3_OS == DT3_IOS
    result = FilePath("{APPDIR}/../Documents");
#endif
}

//==============================================================================
//==============================================================================

std::string HAL::region (void)
{
    /*
    CFLocaleRef locale_ref = ::CFLocaleCopyCurrent();
    CFTypeRef countryRef = ::CFLocaleGetValue(locale_ref, kCFLocaleCountryCode);

    const uint32_t MAX_LOCALE = 128;
    DTcharacter countrycode_c[MAX_LOCALE];
    ::CFStringGetCString((CFStringRef) countryRef, countrycode_c, MAX_LOCALE, kCFStringEncodingASCII);

    CFRelease(locale_ref);

    return countrycode_c ? countrycode_c : NULL;*/
    return std::string();
}

std::string HAL::language (void)
{
    /*
    CFLocaleRef locale_ref = CFLocaleCopyCurrent();

    CFArrayRef langs = ::CFLocaleCopyPreferredLanguages();
    CFStringRef langCode = (CFStringRef) ::CFArrayGetValueAtIndex (langs, 0);

    const uint32_t MAX_LANG = 128;
    DTcharacter languagecode_c[MAX_LANG];
    ::CFStringGetCString((CFStringRef) langCode, languagecode_c, MAX_LANG, kCFStringEncodingASCII);

    CFRelease(locale_ref);
    CFRelease(langs);

    return languagecode_c ? languagecode_c : NULL;
    */
    return std::string();
}

//==============================================================================
//==============================================================================

std::map<StringCopier, Globals::GlobalsEntry> HAL::load_globals (void)
{
    QString app_org;
    QString app_name("DT3");
    if(qApp && !qApp->applicationName().isEmpty()) {
        app_org = qApp->organizationName();
        app_name = qApp->applicationName();
    }
    QSettings prefs(app_org,app_name);
    std::map<StringCopier, Globals::GlobalsEntry> g;
    for(QString name : prefs.allKeys()) {
        QString value = prefs.value(name).toString();
        uint32_t lifetime = Globals::PERSISTENT;

        if (name.startsWith('-')) {
            name.remove(0,1);
            value = MoreStrings::from_obfuscated(name.toStdString(),value.toStdString()).c_str();
            lifetime = Globals::PERSISTENT_OBFUSCATED;
        }

        log("Reading persistent value: " + name.toStdString() + " = " + value.toStdString());

        Globals::GlobalsEntry e;
        e.name = name.toStdString();
        e.value = value.toStdString();
        e.lifetime = lifetime;

        g[name.toStdString()] = e;
    }
    return g;
}

void HAL::save_globals (QHash<QString, Globals::GlobalsEntry> &globals)
{
    QString app_org;
    QString app_name("DT3");
    if(qApp && !qApp->applicationName().isEmpty()) {
        app_org = qApp->organizationName();
        app_name = qApp->applicationName();
    }
    QSettings prefs(app_org,app_name);
    for (const Globals::GlobalsEntry &i : globals) {
        if (i.lifetime == Globals::PERSISTENT || i.lifetime == Globals::PERSISTENT_OBFUSCATED) {
            std::string name = i.name;
            std::string value = i.value;

            if (name.size() <= 0 || value.size() <= 0)
                continue;

            if (i.lifetime == Globals::PERSISTENT_OBFUSCATED) {
                value = MoreStrings::to_obfuscated(name, value);
                name = "-" + name;

                log("Writing persistent value: " + name + " = " + std::string(i.value) + " (Obfuscated form is " + value + ")");
            } else {
                log("Writing persistent value: " + name + " = " + value);
            }
            prefs.setValue(name.c_str(),value.c_str());
        }

    }
}

//==============================================================================
//==============================================================================

} // DT3
