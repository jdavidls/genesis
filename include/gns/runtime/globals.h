#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

  enum gnsGlobalScope {
    GNS_GLOBAL_SCOPE_FIBER = 0x0,
    GNS_GLOBAL_SCOPE_COOP = 0x1,
    GNS_GLOBAL_SCOPE_TASK = 0x2,
    GNS_GLOBAL_SCOPE_ROCESS = 0x3,
  };


# define GNS_GLOBAL_SCOPE_MASK  ( 0x3 << (GNS_ARCH_BITS - 2) )

  struct gnsGlobal {
    gnsNatural id; // SCOPE | INDEX
    // name
    // const gnsType* type;
    gnsBytes data; // if pointer is null, do zerofill initialization

  };


  void gnsGlobalAdd(gnsGlobal*);
  void gnsGlobalDel(gnsGlobal*);

  void* gnsFiberGlobalLookup(gnsGlobal*);


  void gnsGlobalPush(gnsGlobal*);
  void gnsGlobalPop(gnsGlobal*);

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  using GlobalScope = gnsGlobalScope;
  //constexpr auto ggg = gnsFiberGlobalLookup;

  template<typename T, GlobalScope kind>
    struct Global: gnsGlobal {

      Global(): gnsGlobal{ kind << (GNS_ARCH_BITS - 2) } {
        gnsGlobalAdd(this);
      }
      ~Global() {
        gnsGlobalDel(this);
      }

      operator T& () {
        return *reinterpret_cast<T*>(gnsFiberGlobalLookup(this));
      };
    };


}
#endif
