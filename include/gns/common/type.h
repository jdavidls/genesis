#pragma once

#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

  struct gnsReflector; // the entity of reflection
  struct gnsCast;

  typedef GNS_ARRAY_TYPE(gnsCast, 1) gnsCasts;



  struct gnsCast {
    gnsInteger offset;
    struct gnsReflector* type;
  };

  struct gnsReflector {
    gnsCasts hierarchy;
  };
/*
  struct gnsAccessor {
    gnsReflector
  };
*/

GNS_C_LINKAGE_END

#ifdef __cplusplus

namespace gns {

  struct Type {
    const gnsType* self;



  };

  struct TypeMembership {
    //const gnsTypeMember*
  };

}

#endif
