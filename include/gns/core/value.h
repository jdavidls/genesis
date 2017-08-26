/* -*- C++ -*- */
#pragma once

#include <gns/common/basics.h>

typedef struct gnsValueStructure const* gnsValue;
typedef struct gnsTypeStructure const* gnsType;

typedef struct gnsAllocatorStructure const* gnsAllocator;


GNS_C_LINKAGE_BEGIN

  gnsValue gnsAllocate(gnsAllocator, const gnsType, gnsNatural rank, ...);
  void gnsDeallocate(gnsValue);

    // <gns/core/arithmetic>
  gnsValue gnsAdd(gnsValue, gnsValue);
  gnsValue gnsSub(gnsValue, gnsValue);

  gnsValue gnsMul(gnsValue, gnsValue);
  gnsValue gnsDiv(gnsValue, gnsValue);
  gnsValue gnsMod(gnsValue, gnsValue);

GNS_C_LINKAGE_END


#ifdef __cplusplus
namespace gns {
/*
  //template<typename
  struct Allocator {

  }
*/
  struct Value {

    // auto isVariable() => Boolean {}
    // auto isConstant() => Boolean {}



  };

}
#endif
