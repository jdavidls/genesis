/*

# References

LINUX SIGNALS IN C/C++ [ftp://linuxmafia.com/kb/Devtools/signals.html#SECT5.2]


*/
#include "thread.hxx"
#include "process.hxx"

static gnsProcess currentProcess = {

};

const volatile gnsProcess *gnsProcessStartup() {

  // stablish global signal handlers

  // set signal mask


  currentProcess.mainThread = gnsThreadStartup();

  return &currentProcess;
}

void gnsProcessShutdown() {

  gnsThreadShutdown();
}

//void handler()
