#pragma once

#include <gns/common/defines.h>
#include <gns/common/basics.h>

#include <atomic>
#include <semaphore.h>

struct gnsSemaphore {
  sem_t self;
};

// gnsSemaphoreConstructor
// gnsSemaphoreDestructor
// gnsSemaphoreGetValue
// gnsSemaphoreWait
// gnsSemaphoreNotify

namespace gns {

  struct Semaphore: gnsSemaphore {
    GNS_DECLARE_NON_COPYABLE(Semaphore);

    Semaphore(unsigned init = 0) {
      sem_init(&self, 0, init);
    }

    ~Semaphore() {
      sem_destroy(&self);
    }

    operator int() {
      int result;
      GNS_ASSERT( sem_getvalue(&self, &result) == 0 );
      return result;
    }

    void wait() {
      while( sem_wait(&self) == -1 /* IF DEBUG  && errno == EINTR*/ )
        continue;
    }

    void notify(unsigned count = 1) {
      while( count > 0 ) {
        GNS_ASSERT( sem_post(&self) );
        count--;
      }
    }
  };

}
