#pragma once

// ---------------------------
// Platform-specific imports
// ---------------------------
#if CURRENT_PLATFORM == PLATFORM_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    // Logger system
    #include "platform/windows/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_LINUX
    #include <unistd.h>
    #include <pthread.h>
    #include <dlfcn.h>

    // Logger system
    #include "platform/linux/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_MACOS
    #include <unistd.h>
    #include <pthread.h>
    #include <dlfcn.h>
    #include <TargetConditionals.h>

    // Logger system
    #include "platform/macos/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_ANDROID
    #include <jni.h>
    #include <android/log.h>
    #include "AndroidLogger.h"

    // Logger system
    #include "platform/android/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_IOS
    #include <TargetConditionals.h>

    // Logger system
    #include "platform/ios/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_TVOS
    #include <TargetConditionals.h>

    // Logger system
    #include "platform/tvos/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_PLAYSTATION
    // Logger system
    #include "platform/playstation/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_XBOX
    // Logger system
    #include "platform/xbox/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_WEB
    #include <emscripten.h>

    // Logger system
    #include "platform/web/logger/logger.h"
#else
    #error "Unsupported platform: no default imports"
#endif