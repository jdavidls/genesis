#include "thread.hxx"
#include "fiber.hxx"

GNS_LOCAL thread_local gnsThreadStructure gnsThreadInstance;

gnsThread gnsThreadStartup() {
  gnsCurrentFiber = &gnsThreadInstance.mainFiber;

  gnsThreadInstance.auxFiber = gnsFiberAllocate();

  return &gnsThreadInstance;
}

void gnsThreadShutdown() {
}
