#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

  enum gnsGlobalScope {
    GNS_GLOBAL_SCOPE_FIBER = 0x0,
    GNS_GLOBAL_SCOPE_COOP = 0x1,
    GNS_GLOBAL_SCOPE_TASK = 0x2,
    GNS_GLOBAL_SCOPE_ROCESS = 0x3,
  };

# define GNS_GLOBAL_SCOPE_SHIFT  (GNS_ARCH_BITS - 2)
# define GNS_GLOBAL_SCOPE_MASK  ( 0x3 << GNS_GLOBAL_SCOPE_SHIFT )
# define GNS_GLOBAL_INDEX_MASK  ( (1 << GNS_GLOBAL_SCOPE_SHIFT) - 1 )

  struct gnsGlobal {
    gnsNatural id; // SCOPE | INDEX
    // name
    // const gnsType* type;
    gnsBytes data; // if pointer is null, do zerofill initialization

  };


  void gnsGlobalAdd(gnsGlobal*);
  void gnsGlobalDel(gnsGlobal*);

  void* gnsFiberGlobalLookup(gnsGlobal*);
  const volatile void* gnsProcessGlobalLookup(gnsGlobal*);


  void gnsGlobalPush(gnsGlobal*);
  void gnsGlobalPop(gnsGlobal*);

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  using GlobalScope = gnsGlobalScope;
  //constexpr auto ggg = gnsFiberGlobalLookup;

  template<GlobalScope scope, typename T>
    struct Global: gnsGlobal {

      Global(): gnsGlobal{ scope << GNS_GLOBAL_SCOPE_SHIFT } {
        gnsGlobalAdd(this);
      }
      ~Global() {
        gnsGlobalDel(this);
      }

      operator Global<scope, void>&() {
        return *reinterpret_cast<Global<scope, void>*>(this);
      }
    };

  template<typename T>
    struct FiberGlobal: Global<GNS_GLOBAL_SCOPE_FIBER, T> {
      operator T& () {
        return *reinterpret_cast<T*>(gnsFiberGlobalLookup(this));
      };
    };

  template<GlobalScope scope, typename T>
    struct ReadableGuard {
      //
      // operator const T& ()
    };

  template<GlobalScope scope, typename T>
    struct WritableGuard {
      // operator T& ()
    };
}
#endif
