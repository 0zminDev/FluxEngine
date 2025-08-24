#pragma once

#if defined(_WIN32)
    #if defined(FLUX_EXPORT)
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT
#endif