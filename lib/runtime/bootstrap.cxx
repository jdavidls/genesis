#include <iostream>
#include "process.hxx"


__attribute__((constructor)) void gnsStartup(void) {
  std::cout << "startup" << std::endl;

  gnsProcessStartup();
}



__attribute__((destructor)) void gnsShutdown(void) {
  std::cout << "shutdown" << std::endl;
  gnsProcessShutdown();
}
