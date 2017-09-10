#pragma once

#include <gns/common/basics.h>


GNS_CODE_C(
  struct gnsThread;

  extern gnsThread* gnsThreadStartup();
  extern gnsThread* gnsThreadGetCurrent();
  extern void gnsThreadShutdown();

)
GNS_CODE_CXX(

  struct Thread;

)
