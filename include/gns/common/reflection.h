/*

  el concepto method binding es un tipo de objeto invokable
   using Invokable = Object<Invokator>

*/
#pragma once

#include <gns/common/defines.h>
#include <gns/common/basics.h>

#define $_HEAD($, ...) $
#define $_BODY($, ...) __VA_ARGS__

#define GNS_FORWARD_DECLARE(StructureTypeName, ...)                           \
  GNS_CODE_C(                                                                 \
    $_HEAD(__VA_ARGS__) gns ## StructureTypeName;                             \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    $_BODY(__VA_ARGS__)                                                       \
      $_HEAD(__VA_ARGS__)                                                     \
        StructureTypeName;                                                    \
  )

// LOW LEVEL REFLECTION
GNS_FORWARD_DECLARE(Layout, struct);
GNS_FORWARD_DECLARE(LayoutPointer, struct);
GNS_FORWARD_DECLARE(LayoutArray, struct);
GNS_FORWARD_DECLARE(LayoutStructure, struct);

// HIGH LEVEL REFLECTION
GNS_FORWARD_DECLARE(Type, struct);




/*******************************************************************************
/ # Cast
/******************************************************************************/

GNS_CODE_CXX(

template<typename Interface>
  struct Cast {
    using InterfaceType = Interface;
    Integer offset;
    Interface * interface;
  };
)

#define GNS_CAST_DECLARE(CastTypeName, InterfaceTypeName)                     \
  GNS_CODE_C(                                                                 \
    struct gns ## CastTypeName {                                              \
      gnsInteger offset;                                                      \
      GNS_SYMBOL_C(InterfaceTypeName) * interface;                            \
    };                                                                        \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    using CastTypeName = Cast<GNS_SYMBOL_CXX(InterfaceTypeName)>;             \
  )                                                                           \
  GNS_COMPAT_DECLARE(CastTypeName)

/*******************************************************************************
/ # Basic reflector
/******************************************************************************/

GNS_CAST_DECLARE(LayoutCast, Layout);
GNS_ARRAY_DECLARE(LayoutCasts, LayoutCast);

GNS_CAST_DECLARE(TypeCast, Type);
GNS_ARRAY_DECLARE(TypeCasts, TypeCast);

GNS_CODE_C(
  struct gnsReflector {
    gnsTypeCasts hierarchy;
  };
)
GNS_CODE_CXX(
  struct Reflector {
    TypeCasts hierarchy;
  };
)


/*******************************************************************************
/ # Basic Layout
/******************************************************************************/

GNS_CODE_C(
  struct gnsLayout {
    gnsReflector reflector;
    // size, align,
  };
)
GNS_CODE_CXX(
  struct Layout: gnsLayout {
  };
)
GNS_COMPAT_DECLARE(Layout)

/*******************************************************************************
/ # Pointer Layout
/******************************************************************************/

struct gnsLayoutPointer {
  gnsLayout layout;
  gnsReflector* target;
};

/*******************************************************************************
/ # Array Layout
/******************************************************************************/

struct gnsLayoutArray {
  gnsLayout layout;
  gnsNaturals extent;
  gnsLayout* elementLayout;
};

/*******************************************************************************
/ # Strucure Layout
/******************************************************************************/

GNS_CODE_C(
  struct gnsLayoutStructureMember {
    gnsLayout* layout;
  };
)
GNS_CODE_CXX(
  struct LayoutStructureMember: gnsLayoutStructureMember {

  };
)
GNS_COMPAT_DECLARE(LayoutStructureMember)

GNS_ARRAY_DECLARE(LayoutStructureMembeship, LayoutStructureMember);


GNS_CODE_C(
  struct gnsLayoutStructure {
    gnsLayout layout;
    //gnsLayoutStructureMembership membership;
  };
)
GNS_CODE_CXX(
  union LayoutStructureMembershipProperty {
    gnsLayoutStructure  self;
    // retuns a ArrayView of properties.
/*
    operator const LayoutStructureMembeship() const {
    }
    operator LayoutStructureMembeship() {
    }*/
  };

  struct LayoutStructure {
    gnsLayoutStructure  self;
    LayoutStructureMembershipProperty membership;
  };
)




/*******************************************************************************
/ # Function Prototypes
/******************************************************************************/


struct gnsPrototype {

};

struct gnsType {

  // type properties
  // indexar una propiedad de un tipo, retorna un Object<Reflector> (Any)
  //
};

/*
  La propiedades esta mapeadas por strings
*/
struct gnsTypeProperty {

};
// Method es un
struct gnsPropertyMethod {
  // function *
};
//GNS_C_LINKAGE_END
