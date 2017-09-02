#pragma once

#include <gns/common/basics.h>


GNS_C_LINKAGE_BEGIN

  struct gnsThread;

  const volatile gnsThread* gnsThreadStartup();
  void gnsThreadShutdown();

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  struct Thread {
  };
}
#endif
