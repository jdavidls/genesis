#include "thread.hxx"
#include "process.hxx"

GNS_LOCAL gnsProcessStructure gnsProcessInstance;

gnsProcess gnsProcessStartup() {

  gnsProcessInstance.mainThread = gnsThreadStartup();

  return &gnsProcessInstance;
}

void gnsProcessShutdown() {

  gnsThreadShutdown();
}
