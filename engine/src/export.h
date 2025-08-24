#pragma once

#include "defines.h"
#include "types.h"

#include "logger/logger.h"

// ---------------------------
// Platform-specific imports
// ---------------------------
#if CURRENT_PLATFORM == PLATFORM_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#elif CURRENT_PLATFORM == PLATFORM_LINUX
    #include <unistd.h>
    #include <pthread.h>
    #include <dlfcn.h>
#elif CURRENT_PLATFORM == PLATFORM_MACOS
    #include <unistd.h>
    #include <pthread.h>
    #include <dlfcn.h>
    #include <TargetConditionals.h>
#elif CURRENT_PLATFORM == PLATFORM_ANDROID
    #include <jni.h>
    #include <android/log.h>
#elif CURRENT_PLATFORM == PLATFORM_WEB
    #include <emscripten.h>
#else
    #error "Unsupported platform: no default imports"
#endif