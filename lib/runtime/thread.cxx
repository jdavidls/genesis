#include "thread.hxx"
#include "fiber.hxx"

using namespace gns;

static thread_local Fiber fiber;
static thread_local Thread thread;

gnsThread* gnsThreadStartup() {
  gnsFiberStartup(&fiber);

  thread.fiber = &fiber;
  thread.auxFiber = gnsFiberAllocate();

  return reinterpret_cast<gnsThread*>(&thread);
}

void gnsThreadShutdown() {
  gnsFiberShutdown(&fiber);
}




void gnsThreadEntry() {
  gnsThreadStartup();



  gnsThreadShutdown();
}
