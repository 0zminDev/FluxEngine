#pragma once

#if defined(_WIN32)
    #if defined(FLUX_EXPORT)
        #define EXPORT __declspec(dllexport)
        #define IMPORT __declspec(dllimport)
    #else
        #define EXPORT
        #define IMPORT
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #if defined(FLUX_EXPORT)
        #define EXPORT __attribute__((visibility("default")))
        #define IMPORT __attribute__((visibility("default")))
    #else
        #define EXPORT
        #define IMPORT
    #endif
#else
    #define EXPORT
    #define IMPORT
#endif


#if defined(__GNUC__) || defined(__clang__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

#pragma once

// ---------------------------
// Platform definitions
// ---------------------------
#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX   2
#define PLATFORM_MACOS   3
#define PLATFORM_ANDROID 4
#define PLATFORM_IOS     5
#define PLATFORM_TVOS   6
#define PLATFORM_PLAYSTATION 7
#define PLATFORM_XBOX   8
#define PLATFORM_WEB     9
#define PLATFORM_UNKNOWN 0

#if defined(_WIN32) || defined(_WIN64)
    #define CURRENT_PLATFORM PLATFORM_WINDOWS
#elif defined(__linux__)
    #define CURRENT_PLATFORM PLATFORM_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #define CURRENT_PLATFORM PLATFORM_MACOS
#elif defined(__ANDROID__)
    #define CURRENT_PLATFORM PLATFORM_ANDROID
#elif defined(TARGET_OS_IOS) && TARGET_OS_IOS
    #define CURRENT_PLATFORM PLATFORM_IOS
#elif defined(TARGET_OS_TV) && TARGET_OS_TV
    #define CURRENT_PLATFORM PLATFORM_TVOS
#elif defined(__ORBIS__)
    #define CURRENT_PLATFORM PLATFORM_PLAYSTATION
#elif defined(__XBOXONE__) || defined(_GAMING_XBOX)
    #define CURRENT_PLATFORM PLATFORM_XBOX
#elif defined(__EMSCRIPTEN__)
    #define CURRENT_PLATFORM PLATFORM_WEB
#else
    #define CURRENT_PLATFORM PLATFORM_UNKNOWN
#endif


// ---------------------------
// Compiler definitions
// ---------------------------
#define COMPILER_MSVC   1
#define COMPILER_CLANG  2
#define COMPILER_GCC    3
#define COMPILER_UNKNOWN 0

#if defined(_MSC_VER)
    #define CURRENT_COMPILER COMPILER_MSVC
#elif defined(__clang__)
    #define CURRENT_COMPILER COMPILER_CLANG
#elif defined(__GNUC__)
    #define CURRENT_COMPILER COMPILER_GCC
#else
    #define CURRENT_COMPILER COMPILER_UNKNOWN
#endif


// ---------------------------
// Architecture definitions
// ---------------------------
#define ARCH_X64    1
#define ARCH_X86    2
#define ARCH_ARM64  3
#define ARCH_ARM32  4
#define ARCH_UNKNOWN 0

#if defined(_M_X64) || defined(__x86_64__)
    #define CURRENT_ARCH ARCH_X64
#elif defined(_M_IX86) || defined(__i386__)
    #define CURRENT_ARCH ARCH_X86
#elif defined(__aarch64__)
    #define CURRENT_ARCH ARCH_ARM64
#elif defined(__arm__)
    #define CURRENT_ARCH ARCH_ARM32
#else
    #define CURRENT_ARCH ARCH_UNKNOWN
#endif


// ---------------------------
// Static Asserts – safety
// ---------------------------
#if defined(__cplusplus)
    static_assert(CURRENT_PLATFORM != PLATFORM_UNKNOWN, "Unsupported or unknown platform!");
    static_assert(CURRENT_COMPILER != COMPILER_UNKNOWN, "Unsupported or unknown compiler!");
    static_assert(CURRENT_ARCH != ARCH_UNKNOWN, "Unsupported or unknown architecture!");
    static_assert(CURRENT_ARCH != ARCH_X86, "32-bit x86 builds are not supported!");
    static_assert(CURRENT_ARCH != ARCH_ARM32, "32-bit ARM builds are not supported!");
#endif