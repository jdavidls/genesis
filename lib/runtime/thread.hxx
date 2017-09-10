#pragma once
#include <gns/runtime/thread.h>
#include "fiber.hxx"


GNS_CODE_C(
  struct gnsThread {
    gnsFiber* fiber;
    gnsFiberContinuator* auxFiber;
  };

)

GNS_CODE_CXX(
  struct Thread: gnsThread {

    //Fiber* fiber;
    //FiberTracker* auxFiber;

    //GNS_DECLARE_C_COMPAT(Thread);
    Thread() = default;


  };
)
