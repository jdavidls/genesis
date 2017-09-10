/*

  el concepto method binding es un tipo de objeto invokable
   using Invokable = Object<Invokator>

*/
#pragma once

#include <gns/common/defines.h>
#include <gns/common/basics.h>

// LOW LEVEL REFLECTION
GNS_FORWARD_DECLARE(Layout, struct);
GNS_FORWARD_DECLARE(LayoutPointer, struct);
GNS_FORWARD_DECLARE(LayoutArray, struct);
GNS_FORWARD_DECLARE(LayoutTupleElement, struct);
GNS_FORWARD_DECLARE(LayoutTuple, struct);

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
    struct CastTypeName: Cast<GNS_SYMBOL_CXX(InterfaceTypeName)> {            \
      GNS_DECLARE_C_COMPAT(CastTypeName);                                     \
    };                                                                        \
  )

/*******************************************************************************
/ # Basic reflector
/******************************************************************************/

//GNS_CAST_DECLARE(LayoutCast, Layout);
//GNS_ARRAY_DECLARE(LayoutCasts, LayoutCast);

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
  struct Layout {
    // declare compat -> cast to, construct from....
    Reflector reflector;
  };
)
GNS_COMPAT_DECLARE(Layout)

/*******************************************************************************
/ # Pointer Layout
/******************************************************************************/

GNS_CODE_C(
  struct gnsLayoutPointer {
    gnsLayout layout;
    gnsReflector* target;
  };
)

GNS_CODE_CXX(
  struct LayoutPointer {
    Layout layout;
    Reflector* target;
  };
);

GNS_COMPAT_DECLARE(LayoutPointer);

/*******************************************************************************
/ # Array Layout
/******************************************************************************/

GNS_CODE_C(
  struct gnsLayoutArray {
    gnsLayout layout;
    gnsNaturals extent;
    gnsLayout* elementLayout;
  };
)
GNS_CODE_CXX(
  struct LayoutArray {
    Layout layout;
    Naturals extent;
    Layout* elementLayout;
  };

)
GNS_COMPAT_DECLARE(LayoutArray);

/*******************************************************************************
/ # Tuple Layout
/******************************************************************************/

GNS_CODE_C(
  struct gnsLayoutTupleElement {
    gnsLayout* layout;
  };
)
GNS_CODE_CXX(
  struct LayoutTupleElement {
    Layout* layout;
  };
)

GNS_COMPAT_DECLARE(LayoutTupleElement);
GNS_ARRAY_DECLARE(LayoutTupleElements, LayoutTupleElement);

GNS_CODE_C(
  struct gnsLayoutTuple {
    gnsLayout layout;
    gnsLayoutTupleElements elements;
  };
)
GNS_CODE_CXX(
  struct LayoutTuple {
    Layout layout;
    LayoutTupleElements elements;
  };
)
GNS_COMPAT_DECLARE(LayoutTuple)


/*******************************************************************************
/ # Basic Prototype
/******************************************************************************/

GNS_CODE_C(
  struct gnsPrototype {
    gnsReflector reflector;

  };
)
GNS_CODE_CXX(
  struct Prototype {
    //GNS_DECLARE_C_COMPAT(Prototype);

    Reflector reflector;
    //Layout* input;
    //Layout* output;
  };
)
GNS_COMPAT_DECLARE(Prototype)



/*******************************************************************************
/ # Type is a 2nd level reflector and a interface
/  esto quiere decir que puede apuntar a otras jearquias de reflexion,
/   como layout, (en el caso de funciones el layout es nulo)
/******************************************************************************/

GNS_CODE_C(
  struct gnsType {
    gnsReflector reflector;
    gnsLayout* layout;
  };
)
GNS_CODE_CXX(
  struct Type {
    Reflector reflector;
    Layout* layout;

    //Type* proxyOf; // proxyOf interface.. no vale porque debe saber
    //  como obtener el objeto proxy, debe ser Proxy* proxy;
    // object . isProxy
    //  deproxy -> while(object.isProxy) deproxy;


/*
membership:
  a symbol -> member has

  a member can be:
   - attributes (get set by layout + type & copy)
   - property (get set, by functors)
   - method (a get property)
*/

  };

  struct Attribute {
    Naturals index;
    Type* type;

  };
)
