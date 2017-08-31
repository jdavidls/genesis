#pragma once
#include <setjmp.h>
#include <ucontext.h>

#include <gns/runtime/fiber.h>




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
