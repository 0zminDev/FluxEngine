#pragma once
#include <cstdint>
#include "defines.h"

typedef std::int8_t   i8;
typedef std::int16_t  i16;
typedef std::int32_t  i32;
typedef std::int64_t  i64;

typedef std::uint8_t  u8;
typedef std::uint16_t u16;
typedef std::uint32_t u32;
typedef std::uint64_t u64;

typedef float  f32;
typedef double f64;

typedef bool b8;   // 1 bajt bool
typedef int  b32;  // 4 bajty bool (czasem przydatne w API)

typedef char c8;   // zwykły znak
typedef char16_t c16;
typedef char32_t c32;

STATIC_ASSERT(sizeof(i8)  == 1, "i8 must be 1 byte");
STATIC_ASSERT(sizeof(u8)  == 1, "u8 must be 1 byte");
STATIC_ASSERT(sizeof(i16) == 2, "i16 must be 2 bytes");
STATIC_ASSERT(sizeof(u16) == 2, "u16 must be 2 bytes");
STATIC_ASSERT(sizeof(i32) == 4, "i32 must be 4 bytes");
STATIC_ASSERT(sizeof(u32) == 4, "u32 must be 4 bytes");
STATIC_ASSERT(sizeof(i64) == 8, "i64 must be 8 bytes");
STATIC_ASSERT(sizeof(u64) == 8, "u64 must be 8 bytes");

STATIC_ASSERT(sizeof(f32) == 4, "f32 must be 4 bytes");
STATIC_ASSERT(sizeof(f64) == 8, "f64 must be 8 bytes");

STATIC_ASSERT(sizeof(b8)  == 1, "b8 must be 1 byte");
STATIC_ASSERT(sizeof(b32) == 4, "b32 must be 4 bytes");