#pragma once
#include <setjmp.h>
//#include <ucontext.h>

#include <gns/runtime/fiber.h>



struct gnsFiber {
  gnsBytes stack;
//  gnsNatural length;
//  gnsFiberModuleLocals* module;
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


}
#endif
