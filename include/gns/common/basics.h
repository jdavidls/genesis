/* -*- C++ -*- */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#define GNS_ASSERT(EXPR) \
  for(; !(EXPR); (std::cerr << "Assertion: " #EXPR << std::endl), std::abort() )

#define GNS_GLOBAL  __attribute__ ((visibility ("default")))
#define GNS_LOCAL   __attribute__ ((visibility ("hidden")))

#define GNS_FIBER_LOCAL __attribute((section("gnsfls")))
#define GNS_NO_STRIP __attribute((used))



#ifdef __cplusplus
#define GNS_C_LINKAGE extern "C"
#define GNS_C_LINKAGE_BEGIN GNS_C_LINKAGE {
#define GNS_C_LINKAGE_END }
#define GNS_THREAD_LOCAL thread_local
#define GNS_LOG(EXPR) \
  ( std::cout << (#EXPR) << " = " << (EXPR) << std::endl )
#else
#define GNS_C_LINKAGE extern
#define GNS_C_LINKAGE_BEGIN
#define GNS_C_LINKAGE_END
#define GNS_THREAD_LOCAL _Thread_local
#endif

#define GNS_ARRAY_LENGTH(X) \
  ( sizeof(X) / sizeof(*(X)) )

typedef void gnsUnknow;

typedef struct { int _[0]; } gnsVoid;


typedef bool gnsBit;
typedef uint8_t gnsByte;


typedef uintptr_t gnsNatural;
/*
typedef uint8_t gnsNatural8;
typedef uint16_t gnsNatural16;
typedef uint32_t gnsNatural32;
typedef uint64_t gnsNatural64;
*/
typedef intptr_t gnsInteger;
/*
typedef int8_t gnsInteger8;
typedef int16_t gnsInteger16;
typedef int32_t gnsInteger32;
typedef int64_t gnsInteger64;
*/
typedef double gnsFloatPoint;
/*
typedef float gnsFloatPoint32;
typedef double gnsFloatPoint64;
*/

typedef struct { void* descriptor; void* data; } gnsObject;

#ifdef __cplusplus
#include <iostream>

namespace gns {

  //constexpr auto error = std::cerr;

  using Unknow = gnsUnknow;

  using Bit = gnsBit;
  using Byte = gnsByte;

  using Natural = gnsNatural;
  using Integer = gnsInteger;

  using FloatPoint = gnsFloatPoint;

}

#endif
