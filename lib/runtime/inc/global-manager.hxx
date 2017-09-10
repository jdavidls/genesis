#pragma once
#include <gns/runtime/globals.h>
#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN


GNS_C_LINKAGE_END
#ifdef __cplusplus
namespace gns {

  template<GlobalScope scope>
    struct GlobalDescriptor {
      Global<scope, void>* global; // active when module is loaded
    };


  template<GlobalScope scope>
    struct GlobalEntry {
      Pointer pointer;
      // stack
      // mutex
      // garbage??
    };


  template<GlobalScope scope>
    struct GlobalManager {


      static Array<Global<scope, void>*> globals;
      // puede mantener un listado de huecos en el array global
      // que serán reutilizados

      static void add(Global<scope, void>& global) {
        GNS_ASSERT( global.id & GNS_GLOBAL_SCOPE_MASK == scope << GNS_GLOBAL_SCOPE_SHIFT );

        global.id |= globals.push(&global);
      }

      static void del(Global<scope, void>& global) {
        GNS_ASSERT( global.id & GNS_GLOBAL_SCOPE_MASK == scope << GNS_GLOBAL_SCOPE_SHIFT );

        auto index = global.id & GNS_GLOBAL_INDEX_MASK;
      }

      //////////////////////////////////////////////////////////////////////////

      Array<GlobalEntry<scope>> entries;

      Pointer lookup(const gnsGlobal& global) {
        auto index = global.id & GNS_GLOBAL_INDEX_MASK;

        if( index >= entries.length ) {

          GNS_ASSERT( index < globals.length );
          /*
          obtiene un mutex global, para todo el global manager
            El segmento de globales va a ser reemplazado
            cuando scope = process | task
          */
          entries.length = globals.length;
        }

        auto& entry = entries[index];
        auto pointer = entry.pointer;

        if( pointer == nullptr ) {
          // pointer = entry.pointer = allocate(gnsType, 1);

          // adquiere el entry.mutex para escritura
          //entry.pointer
        }

        return pointer;
      }

    };

}
#endif
