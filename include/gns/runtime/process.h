#pragma once

#include <gns/common/basics.h>

typedef struct gnsProcessStructure* gnsProcess;

GNS_C_LINKAGE_BEGIN

  gnsProcess gnsProcessStartup();
  void gnsProcessShutdown();

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {
  struct Process {
    gnsProcessStructure& self;

    Process(Natural argc, char* argv[]):
      self( *gnsProcessStartup() ) {

    }

    ~Process() {
      gnsProcessShutdown();
    }
  };
}
#endif
