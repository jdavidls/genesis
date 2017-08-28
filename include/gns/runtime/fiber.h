#pragma once

#include <gns/common/basics.h>

// fiber signals..
typedef enum gnsFiberCommand {
  CONTINUE =  1UL << 0,
  THROW =     1UL << 32,
};

typedef struct gnsFiberStructure* gnsFiber;

GNS_C_LINKAGE_BEGIN

  gnsFiber gnsFiberAllocate();

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  class Fiber {
    gnsFiber self;

  public:

    enum State {
      FINISHED = -1,
      RUNNING = 0
    };

    using Command = gnsFiberCommand;


    Fiber() {
      // allocateFiber
      // initializeFiber

    }

    ~Fiber() {

    }


  };

}
#endif
