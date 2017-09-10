/*

  el concepto method binding es un tipo de objeto invokable
   using Invokable = Object<Invokator>

*/
#pragma once

#include <gns/common/defines.h>
#include <gns/common/basics.h>


namespace gns {

  template<typename I>
    struct ObjectABI {
        const I* interface;
        Pointer data;
    };
/*
  template<>
    struct Object
*/
}


#define GNS_DECLARE_OBJECT_TYPENAME(InterfaceTypeName, ObjectTypeName)        \
  GNS_C_LINKAGE_BEGIN                                                         \
    struct gns ## ObjectTypeName {                                            \
      const gns ## InterfaceTypeName * interface;                             \
      gnsPointer data;                                                        \
    };                                                                        \
  GNS_C_LINKAGE_END                                                           \
  namespace gns {                                                             \
    using ObjectTypeName = Object<InterfaceTypeName>;                         \
    template<> struct ObjectCCompat<ElementTypeName> {                        \
      using c_compat_type = :: gns ## ObjectTypeName;                         \
    };                                                                        \
  }

struct gnsInvokable {
  // ffi_cif ffi;

};

//GNS_DECLARE_OBJECT_TYPENAME(Reflector, Object); the most abstract object
