#pragma once

#include <gns/common/defines>
#include <gns/common/basics>

#define GNS_OBJECT_TYPE(REFLECTOR)  \
struct {                            \
  const REFLECTOR *reflector;       \
  void* instance;                   \
};

//#define GNS_OBJECT_IS_KNOW(O) ((O).reflector)


GNS_C_LINKAGE_BEGIN

  //typedef GNS_OBJECT_TYPE( gnsType ) gnsObject;

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  template<typename Reflector> struct Object;

  /*
  struct Iterable {

    Object(): self{ nullptr, nullptr } {  }


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
