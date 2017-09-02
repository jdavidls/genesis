#include "thread.hxx"
#include "process.hxx"

static gnsProcess currentProcess = {

};

const volatile gnsProcess *gnsProcessStartup() {

  currentProcess.mainThread = gnsThreadStartup();

  return &currentProcess;
}

void gnsProcessShutdown() {

  gnsThreadShutdown();
}
