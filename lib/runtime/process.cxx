/*

# References

LINUX SIGNALS IN C/C++ [ftp://linuxmafia.com/kb/Devtools/signals.html#SECT5.2]


*/
#include "thread.hxx"
#include "process.hxx"

static gnsProcess process;

gnsProcess *gnsProcessStartup() {
  process.thread = gnsThreadStartup();

  return &process;
}

void gnsProcessShutdown() {

  gnsThreadShutdown();
}

//void handler()
