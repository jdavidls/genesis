#pragma once

#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

  struct gnsType;
  struct gnsCast;
  struct gnsReflector; // the entity of reflection
  struct gnsReflectorAncestor;

  struct gnsCast {
    gnsInteger offset;
    gnsType* type;
  };


  struct gnsReflector {
    GNS_ARRAY_TYPE(gnsReflectorAncestor, 1) hierarchy;
  };

  struct gnsReflectorAncestor {
    gnsCast upcast;
  };


////////////////////////////////////////////////////////////
# define GNS_REFLECTION_LEVEL__Type 1
# define GNS_TYPE_HEAD()  \
    struct {              \
      gnsType type;       \
    }


  struct gnsType {
    // ffi_type* ffi;

    // gnsTypeAccessor constant
    // gnsTypeAccessor variable

  };

  struct gnsStructureMember {
    gnsCast downcast;
  };

# define GNS_REFLECTION_LEVEL__Structure (GNS_REFLECTION_LEVEL__Type + 1)
  struct gnsStructure {
    GNS_TYPE_HEAD();

    GNS_ARRAY_TYPE(gnsStructureMember, 1) membership;
  };


GNS_C_LINKAGE_END

#ifdef __cplusplus

namespace gns {

  struct Type {
    const gnsType* self;

    Type(const gnsType* type): self(type) {}
    operator const gnsType* () { return self; }


  };

  struct TypeMembership {
    //const gnsTypeMember*
  };

}

#endif
