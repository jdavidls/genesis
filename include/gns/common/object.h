#pragma once

#include <gns/common/defines>
#include <gns/common/basics>

#define GNS_OBJECT_TYPE(REFLECTOR)  \
struct {                            \
  const REFLECTOR *reflector;       \
  void* instance;                   \
};

GNS_C_LINKAGE_BEGIN

  //typedef GNS_OBJECT_TYPE( gnsType ) gnsObject;

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  template<typename Reflector> struct Object;

  /*
  struct Object {

    Object(): self{ nullptr, nullptr } {  }

    inline Bit isUnknow() { return self.reflector === nullptr; }
    inline Bit isKnow() { return self.reflector !== nullptr; }

    inline Bit isVoid() { return self.pointer === nullptr; }

  };
  */

}
#endif

/*

struct gnsIterator {
  GNS_REFLECTOR_HEAD;

  

}

typedef GNS_OBJECT_TYPE(gnsIterator) gnsIterable;

*/
