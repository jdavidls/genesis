#pragma once

#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

  struct gnsType;
  struct gnsCast;
  struct gnsReflector; // the entity of reflection
  struct gnsReflectorAncestor;

  struct gnsCast {
    gnsType* type;
    gnsInteger offset;
  };

  struct gnsReflector {
    GNS_ARRAY_TYPE(gnsReflectorAncestor, 1) hierarchy;
  };

  struct gnsReflectorAncestor {
    gnsCast upcast;
  };


////////////////////////////////////////////////////////////
# define GNS_REFLECTION_LEVEL__Type 1

  // no es constructible, estanciable etc.
  // Object<Reflector> reflectable;
  // Object<Iterator> iterable
  // Object<Descriptor> descriptable -> type
  // Object<Constructor> constructible (default)
  // Object<Invokator> invokable; -> function

  struct gnsInvokator {
    gnsReflector reflector;
  };

  //
  struct gnsConstructor {
    ffi_type ffi;

    // gnsBytes init; este atributo puede estar desnormalizado,
    // se normalizará a traves de la llamada al atributo
    // Type->initBuffer

    // constructor
    // destructor

    gnsReflector reflector;

    // gnsTypeAccessor constant
    // gnsTypeAccessor variable

  };

  // los dereferenciadores (proxies), tienen
  
  struct gnsPointer { // dereferenciator -> dereferenciable
    gnsConstructor type;
    const gnsReflector* target;
  };

  struct gnsStructureMember {
    gnsCast cast;
    //gnsReflector reflector;
  };

  struct gnsStructure {
    //gnsConstructor
    // embership
    // iterator (membership iterator)
    // invokator object invokator

  };

  export const gnsType *gnsTypeVoid;
  export const gnsType *gnsTypeVoid;
  export const gnsType *gnsTypeInteger;


GNS_C_LINKAGE_END

#ifdef __cplusplus

namespace gns {
/*
  template<typename Up, typename Down>
    struct Cast {

    };
*/
  struct Reflector: gnsReflector {

  };

  struct Type: gnsType {
    static constexpr Natural level = 1;

  };

  struct Structure: gnsStructure {
    static constexpr Natural level = Type::level + 1;
  };


}

#endif
