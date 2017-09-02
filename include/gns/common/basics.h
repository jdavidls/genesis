/* -*- C++ -*- */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <gns/common/defines.h>

GNS_C_LINKAGE_BEGIN

# define GNS_ARCH_BITS ( sizeof(intptr_t) * 8 )


  typedef struct { int _[0]; } gnsEmpty;
  typedef bool gnsBit;
  typedef uint8_t gnsByte;
  typedef void* gnsPointer;


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



  #define GNS_ARRAY_TYPE(TYPE, RANK)                                            \
    struct {                                                                    \
      gnsNatural extent[RANK];                                                  \
      TYPE * pointer;                                                           \
    }

  #define GNS_ARRAY_INIT(EXTENT, POINTER) { EXTENT, POINTER }

  typedef GNS_ARRAY_TYPE(gnsByte, 1) gnsBytes;
  typedef GNS_ARRAY_TYPE(gnsPointer, 1) gnsPointers;

  typedef GNS_ARRAY_TYPE(const gnsByte, 1) gnsInmutableBytes;
  typedef GNS_ARRAY_TYPE(const gnsPointer, 1) gnsInmutablePointers;


  #define GNS_TEXT(S) { { GNS_C_ARRAY_LENGTH(S) }, S }

GNS_C_LINKAGE_END

#ifdef __cplusplus

#include <iostream> // FOR ASSERT

namespace gns {

  using Empty = gnsEmpty;
  using Bit = gnsBit;
  using Byte = gnsByte;
  using Pointer = gnsPointer;

  using Natural = gnsNatural;
  using Natural8 = gnsNatural8;
  using Natural16 = gnsNatural16;
  using Natural32 = gnsNatural32;
  using Natural64 = gnsNatural64;

  using Integer = gnsInteger;
  using Integer8 = gnsInteger8;
  using Integer16 = gnsInteger16;
  using Integer32 = gnsInteger32;
  using Integer64 = gnsInteger64;

  using FloatPoint = gnsFloatPoint;
  using FloatPoint32 = gnsFloatPoint32;
  using FloatPoint64 = gnsFloatPoint64;

}

#endif
