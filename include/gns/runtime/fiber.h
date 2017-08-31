#pragma once

#include <gns/common/basics.h>


GNS_C_LINKAGE_BEGIN

# define GNS_FIBER_CALLTHROUGH 0

  struct gnsFiberTracker {
    struct gnsFiberContinuator * continuator;
  };

  gnsFiberTracker gnsFiberAllocate();

GNS_C_LINKAGE_END

#ifdef __cplusplus
namespace gns {

  class Fiber {
  };

}
#endif
