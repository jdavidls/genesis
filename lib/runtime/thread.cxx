#include "thread.hxx"
#include "fiber.hxx"

static thread_local gnsThread currentThread;

const volatile gnsThread* gnsThreadStartup() {
  //gnsCurrentFiber = &gnsThreadInstance.mainFiber;

  //gnsThreadInstance.auxFiber = gnsFiberAllocate();

  return &currentThread;
}

void gnsThreadShutdown() {
}
