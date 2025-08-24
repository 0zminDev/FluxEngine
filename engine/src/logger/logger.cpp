#include "logger.h"

EXPORT void log_message(const c8* msg) {
    #if CURRENT_PLATFORM == PLATFORM_WINDOWS
        MessageBoxA(NULL, msg, "Log", MB_OK);
    #elif CURRENT_PLATFORM == PLATFORM_ANDROID
        __android_log_print(ANDROID_LOG_INFO, "FluxEngine", "%s", msg);
    #else
        printf("%s\n", msg);
    #endif
}
