#pragma once
#include <setjmp.h>
//#include <ucontext.h>

#include <gns/runtime/fiber.h>
#include "inc/global-manager.hxx"

using namespace gns;

struct gnsFiber {

  GlobalManager<GNS_GLOBAL_SCOPE_FIBER> globalManager;

  gnsBytes stack;
};

extern gnsFiber *gnsFiberGetCurrent();
//extern gnsFiber *gnsFiberSetCurrent(gnsFiber *);

// at fiber server
struct gnsFiberContinuator {

  // INPUT DATA

  gnsFiberTracker * tracker;

  // OUTPUT DATA:
  union {
    jmp_buf jumpBuffer;
    //sigjmp_buf jumpBuffer;
    //ucontext_t ucontext;
  };
};


#ifdef __cplusplus
namespace gns {
  struct Fiber: gnsFiber {



  };

  struct FiberContinuator: gnsFiberContinuator {

  };

}
#endif
