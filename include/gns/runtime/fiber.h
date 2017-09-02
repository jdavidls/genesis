#pragma once

#include <gns/common/defines.h>
#include <gns/common/basics.h>

#ifdef __cplusplus
# define GNS_DECLTYPE(...)                                                          \
    decltype(__VA_ARGS__)
#else
# define GNS_DECLTYPE(...)                                                          \
    typeof(__VA_ARGS__)
#endif

#define GNS_FIBER_LOCAL_DECL(...)                                                   \
  GNS_ATTR_SECTION(FIBER_LOCAL) extern ::gns::FiberLocal<__VA_ARGS__>

#define GNS_FIBER_LOCAL_DEF(...)                                                    \
  GNS_ATTR_SECTION(FIBER_LOCAL) ::gns::FiberLocal<__VA_ARGS__>

#define GNS_FIBER_LOCAL_LOOKUP(VAR, POINTER_TYPE) ({                                \
  GNS_ASSERT( GNS_SECTION_CONTAINS(FIBER_LOCAL, &(VAR)) );                          \
  *(POINTER_TYPE) (                                                                 \
    GNS_SECTION_START(FIBER_LOCAL) +                                                \
    GNS_SECTION_OFFSET_OF(FIBER_LOCAL, &(VAR)) );                                   \
})
/*
#define GNS_FIBER_LOCAL_MODULE_ADDRESS(MODULE_IDX) ({

})
*/
#define GNS_FIBER_LOCAL(VAR) GNS_FIBER_LOCAL_LOOKUP(VAR, GNS_DECLTYPE(&VAR))

GNS_C_LINKAGE_BEGIN
/*
# define GNS_FIBER_LOCAL_SECTION                                                    \
    GNS_SECTION_DEFINE("", GNS_SECTION_READOLY)
*/

  GNS_SECTION_DECLARE(FIBER_LOCAL);



  enum gnsFiberCommand {
    GNS_FIBER_CALLTHROUGH = 0,
    GNS_FIBER_CONTINUE = 1,

    // UNWIND COMMANDS here? retrieve unwin context is posible:
    // jump to fiber, save context in caller stack (unwins get context)
    // an jump back
  };

  struct gnsFiberTracker {
    struct gnsFiberContinuator * continuator;
  };

  gnsFiberTracker gnsFiberAllocate();

  gnsFiberCommand gnsFiberJump(gnsFiberTracker * tracker, gnsFiberCommand sendCmd);
  //gnsPointer gnsFiberSegmentLookup(gnsNatural fiberSegmentId);
  //gnsPointer gnsFiberSegmentLookup(gnsNatural fiberSegmentId);

  // typedef gnsFiberContinuator gnsFiberEntry(gnsFiberContinuator, ...);

GNS_C_LINKAGE_END

#ifdef __cplusplus
# include<iostream>

namespace gns {

  using FiberCommand = gnsFiberCommand;

  struct FiberTracker: public gnsFiberTracker {


    FiberTracker():
      gnsFiberTracker{ gnsFiberAllocate() }
    { }

    FiberTracker(gnsFiberContinuator*&& continuator):
      gnsFiberTracker{continuator}
    {
      //tracker.continuator == nullptr;
    }

    ~FiberTracker() {
/*
  enviar un fiber termination debe ir en el

      if( continuator ) {
        // raise a fiberTermination exception..
      }
*/
    }

    FiberCommand jump(FiberCommand cmd = GNS_FIBER_CONTINUE) {
      return gnsFiberJump(this, cmd);
    }


  };

  template<typename T>
    struct FiberLocal {

      T initValue;

      FiberLocal(const T& init): initValue(init) {
        GNS_ASSERT( GNS_SECTION_CONTAINS(FIBER_LOCAL, this) );
      }
/*
      operator T&() {

      }

      // T* operator -> () {}
      T* operator & () {
        return nullptr;
      }

      void operator = (const T& value) {

      }
*/

    };

}
#endif
