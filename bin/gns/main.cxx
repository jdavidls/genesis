#include <iostream>

#include <gns/common/basics.h>
#include <gns/runtime/fiber.h>
#include <gns/runtime/process.h>

#include <gns/common/reflection.h>

using namespace gns;



int main(int argc, char* argv[]) {
  Process proc(argc, argv);


//  auto ref = GNS_FIBER_LOCAL_LOOKUP(local, decltype(&local.initValue));
  Array<int> array({1,2,3});

  //++array.length ;
  --array.length;
  array.push(7);


  GNS_LOG( sizeof(array) );
  GNS_LOG( array.length );
  GNS_LOG( array[-1] );

/*
  GNS_LOG( GNS_SECTION_SIZE(fiber_local) );
  GNS_LOG( GNS_SECTION_OFFSET_OF(fiber_local, myVar) );
  GNS_LOG( GNS_SECTION_CONTAINS(fiber_local, myVar) );
*/
/*
  Fiber fiber;
  GNS_LOG( fiber.continuator );
*/

  return 0;
}
