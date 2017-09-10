#pragma once

#include <gns/common/basics.h>

GNS_FORWARD_DECLARE(Process, struct);

GNS_CODE_C(
  extern gnsProcess* gnsProcessStartup();
  extern void gnsProcessShutdown();
);


GNS_CODE_CXX(
/*
  struct Process {
    static
    const volatile ProcessContext& self;

    Process(Natural argc, char* argv[]):
      self( *gnsProcessStartup(argc, argv) ) {

    }

    ~Process() {
      gnsProcessShutdown();
    }
  };*/
);
