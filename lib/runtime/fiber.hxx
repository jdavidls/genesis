#pragma once
#include <setjmp.h>
//#include <ucontext.h>

#include <gns/runtime/fiber.h>
//#include "inc/global-manager.hxx"

GNS_FORWARD_DECLARE(Fiber, struct);

GNS_CODE_C(

  struct gnsFiber: gnsEmpty {
  };

  struct gnsFiberContinuator {
    Fiber* fiber;
    jmp_buf jumpBuffer;
  };


  extern void gnsFiberStartup(gnsFiber* self);
  extern void gnsFiberShutdown(gnsFiber* self);

)

GNS_CODE_CXX(

  struct Fiber: gnsFiber {
    //FiberContinuator* continuator;
    //Bytes stack;

    // fiber next user data structure.

    // es itneresante utilziar el fiber next data structure porque
    // es en realidad la estructura que lo controla
    // desde mecanismos de mas alto nivel.
    // por ejemplo,

  };

  struct FiberContinuator: gnsFiberContinuator {

  };


)
