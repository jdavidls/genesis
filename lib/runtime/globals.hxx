#pragma once
#include <gns/runtime/globals.h>
#include <gns/common/array.h>

GNS_C_LINKAGE_BEGIN


GNS_C_LINKAGE_END
#ifdef __cplusplus
namespace gns {

  template<GlobalScope scope>
    struct GlobalManager {

      static Array<gnsGlobal> globals;
      // puede mantener un listado de huecos en el array global
      // que serán reutilizados

      static void add(gnsGlobal& global) {
        GNS_ASSERT(global.id & GNS_GLOBAL_SCOPE_MASK == scope);
        global.id |= globals.push(global);
      }

      static void del(gnsGlobal& global) {
        //global.id & GNS_GLOBAL_SCOPE_MASK
      }


///////

      struct Entry {
        Pointer pointer;
      };

      Array<Entry> entries;


      // IDEA: utilizar volatile como cualificador de la estancia del manager.

/*
      static GNS_ARRAY_TYPE(gnsSegmentDescriptor*, 1) descriptors;// = { {0}};


      static void add(gnsSegmentDescriptor& descriptor) {
        descriptor.idx = GNS_ARRAY_LENGTH(descriptors);

        // agrega un descriptor a descriptors
        // asigna su id,
        // si existen descriptores
      }

      struct Entry {
        gnsPointer pointer;
        // pushed segments
      };
      //static registeredSegments;

      GNS_ARRAY_TYPE(Entry, 1) entries = { {0}, nullptr };
      //Ref<Entry, 1> entries;
      */
    };

}
#endif
