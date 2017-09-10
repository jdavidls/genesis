#pragma once
#include <gns/runtime/process.h>

#include "thread.hxx"

GNS_CODE_C(
  struct gnsProcess {
    gnsThread * thread;
  };
)

GNS_CODE_CXX(
  struct Process {
    GNS_DECLARE_C_COMPAT(Process);

    Thread* thread;
  };
)
