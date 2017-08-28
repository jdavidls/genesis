#pragma once

#include <gns/common/basics.h>

typedef struct gnsThreadStructure* gnsThread;

GNS_C_LINKAGE_BEGIN

  gnsThread gnsThreadStartup();
  void gnsThreadShutdown();

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  struct Thread {
  };
}
#endif
