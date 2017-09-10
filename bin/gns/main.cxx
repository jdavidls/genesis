#include <iostream>

#include <gns/common/basics.h>
#include <gns/runtime/fiber.h>
#include <gns/runtime/process.h>

#include <gns/common/reflection.h>

using namespace gns;



int main(int argc, char* argv[]) {
//  auto ref = GNS_FIBER_LOCAL_LOOKUP(local, decltype(&local.initValue));

  FiberTracker tracker;

  GNS_LOG( tracker.continuator );


  Array<int> array({1,2,3});

  //++array.length ;
  --array.length;
  array.push(7);


  GNS_LOG( sizeof(array) );
  GNS_LOG( array.length );
  GNS_LOG( array[-1] );

  return 0;
}
