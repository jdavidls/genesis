#pragma once

#include <gns/common/basics.h>

GNS_C_LINKAGE_BEGIN

  struct gnsProcess;

  const volatile gnsProcess *
    gnsProcessStartup();

  void
    gnsProcessShutdown();

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  struct Process {
    const volatile gnsProcess& self;

    Process(Natural argc, char* argv[]):
      self( *gnsProcessStartup() ) {

    }

    ~Process() {
      gnsProcessShutdown();
    }
  };
}
#endif
