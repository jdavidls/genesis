#pragma once

#include <gns/common/defines.h>
#include <gns/common/array.h>

GNS_C_LINKAGE_BEGIN

  //GNS_SECTION_DECLARE(GNS_MODULE_MANIFEST);

  # define GNS_MODULE_GENERIC_GLOBAL()                                         \
      struct {                                                                 \
        gnsModuleGlobalKind kind;                                              \
      }

  struct gnsModuleManifest;

  union gnsModuleGlobal;
  typedef GNS_MODULE_GENERIC_GLOBAL() gnsModuleGenericGlobal;
  typedef GNS_ARRAY_TYPE(gnsModuleGlobal) gnsModuleGlobals;


  struct gnsSegment {
      // fault: auto push / error

    gnsBytes area;
      // if pointer is nullptr -> calloc.
      // all segments are allocated in cache align
  };

  // for dynamic linking
  struct gnsModuleManifest {
    // module name
    // version
    // license
    // ....etc...
    gnsModuleSegments segments;
    gnsModuleGlobals globals;
  };


  struct gnsModuleProcessGlobal {
    GNS_MODULE_GENERIC_GLOBAL();

    gnsPointer pointer;
  };

  struct gnsModuleFiberGlobal {
    GNS_MODULE_GENERIC_GLOBAL();

    gnsNatural globalSegmentIdx;
    gnsNatural offset;
  };


  struct gnsModuleGlobal {

    //gnsType* type;
    //void(* constructor)(void*);   defaults: [](T* v){ new(v) T(); }
    //void(* destructor)(void*);    defaults: [](T* v){ delete(v) T(); }
    //void(* extends)(void*, void*); defaults: [](T* a, T* b){ *b = *a; }
  };




/*
  struct gnsProcessGlobal;
  //struct gnsThreadGlobal;
  //struct gnsFiberGlobal;
  struct gnsContextGlobal;
*/


  union gnsModuleGlobal {
    gnsProcessGlobal processGlobal;
    //gnsThreadGlobal threadGlobal;
    //gnsFiberGlobal fiberGlobal;
    gnsContextGlobal fiberGlobal;
  };


GNS_C_LINKAGE_END


#ifdef __cplusplus
namespace gns {
  /*
  // Kind of global
  enum GlobalScope {
    PROCESS,
    THREAD,
    FIBER,
    CONTEXT,
  };
*/
  template<typename T, GlobalScope SCOPE>  struct Global;

  template<typename T>
    struct Global<T, GlobalScope::PROCESS> {
      GlobalScope scope = GlobalScope::PROCESS;
      T* pointer;
    };

  template<typename T>
    struct Global<T, GlobalScope::FIBER> {
      GlobalScope scope = GlobalScope::FIBER;
      Natural moduleId;
      T* initialValue;
    };
}
#endif
