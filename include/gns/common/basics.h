/* -*- C++ -*- */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <gns/common/defines.h>

//typedef void gnsUnknow;
//typedef struct { int _[0]; } gnsVoid;

typedef bool gnsBit;
typedef uint8_t gnsByte;


typedef uintptr_t gnsNatural;
typedef uint8_t gnsNatural8;
typedef uint16_t gnsNatural16;
typedef uint32_t gnsNatural32;
typedef uint64_t gnsNatural64;

typedef intptr_t gnsInteger;
typedef int8_t gnsInteger8;
typedef int16_t gnsInteger16;
typedef int32_t gnsInteger32;
typedef int64_t gnsInteger64;

typedef double gnsFloatPoint;
typedef float gnsFloatPoint32;
typedef double gnsFloatPoint64;


#ifdef __cplusplus
//#include <iostream>

namespace gns {

  using Bit = gnsBit;
  using Byte = gnsByte;

  using Natural = gnsNatural;
  using Integer = gnsInteger;

  using FloatPoint = gnsFloatPoint;


}

#endif
