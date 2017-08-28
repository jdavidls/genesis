#include <iostream>

#include <gns/common/basics.h>
#include <gns/runtime/fiber.h>
#include <gns/runtime/process.h>


int main(int argc, char* argv[]) {
  gns::Process proc(argc, argv);


  auto fiber = gnsFiberAllocate();

  GNS_LOG( fiber );


  return 0;
}
