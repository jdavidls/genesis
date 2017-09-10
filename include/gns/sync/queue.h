/*
Cola lock and free apra un productor un consumidor

http://www.drdobbs.com/parallel/writing-lock-free-code-a-corrected-queue/210604448?pgno=2
*/

#include <queue>
#include <mutex>
#include <gns/sync/semaphore.h>


namespace gns {

  template<typename T>
    class SyncQueue {
      GNS_DECLARE_NON_COPYABLE(SyncQueue)

      Semaphore semaphore;
      std::mutex mutex;
      std::queue<T> queue;

    public:

      T pop() noexcept {
        semaphore.wait();

        std::unique_lock<std::mutex> lock(mutex);

        auto value = queue.front();

        queue.pop();

        return value;
      }

      void push(T value) {
        {
          std::unique_lock<std::mutex> lock(mutex);

          queue.push(value);
        }
        semaphore.notify();
      }
    };
}
