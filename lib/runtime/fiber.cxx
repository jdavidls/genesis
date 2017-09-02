#include <iostream>
#include <utility>


#include <sys/mman.h>
#include <ucontext.h>
#include <setjmp.h>
#include <string.h>
#include <errno.h>

#include "fiber.hxx"

using namespace gns;


namespace {
  static thread_local gnsFiber *__currentFiber = nullptr;


  static gnsFiber * gnsFiberSetCurrent(gnsFiber* fiber) {
    auto result = __currentFiber;
    __currentFiber = fiber;
    return result;
  }

  static thread_local struct {
     gnsFiberContinuator* ownerContinuator;
     gnsBytes stack;
  } __fiberInit;
}

gnsFiber * gnsFiberGetCurrent() {
  return __currentFiber;
}


static void gnsFiberEntry();

static Natural pageLength = 4096; // proces global var.
static Natural stackLength = 1*1016*1024;

gnsFiberTracker gnsFiberAllocate() {

  auto stack = reinterpret_cast<Byte*>(mmap(
    0,                                //  address
    stackLength+2*pageLength,         //  length
    PROT_NONE,                        //  prot
    MAP_PRIVATE | MAP_ANONYMOUS,      //  flags
    -1,                               //  fd
    0                                 //  offset
  ));

  GNS_ASSERT( stack != MAP_FAILED )
    std::cerr << "Unable to allocate fiber memory" << strerror(errno) << std::endl;

  GNS_ASSERT( mprotect(stack + pageLength, stackLength, PROT_READ | PROT_WRITE) != -1 )
    std::cerr << "Unable to protect bottom of fiber stack" << strerror(errno) << std::endl;

  gnsFiberTracker tracker;

  gnsFiberContinuator selfContinuator;
  selfContinuator.tracker = &tracker;

  if( setjmp(selfContinuator.jumpBuffer) == 0 ) {
    ucontext_t ucontext;
    GNS_ASSERT( getcontext(&ucontext) != -1 ); // esto puede ser cacheado.

    ucontext.uc_stack.ss_sp = stack + pageLength;
    ucontext.uc_stack.ss_size = stackLength;
    ucontext.uc_link = nullptr; // TODO vincular a un recoletor de fibers.

    __fiberInit.ownerContinuator = &selfContinuator;
    __fiberInit.stack = { { stackLength }, stack };

    // pasa estas variables por thread local
    makecontext(&ucontext, (void(*)())&gnsFiberEntry, 0);

    setcontext(&ucontext);
  }

  return tracker;
}


void gnsFiberEntry() {

  gnsFiber self = {
    __fiberInit.stack

  };

  //auto owner =
  gnsFiberSetCurrent(&self);


  FiberTracker ownerTracker( std::move(__fiberInit.ownerContinuator) );



  GNS_LOG(ownerTracker.continuator);

  while(true) {

    //gnsFiberStartup();

    ownerTracker.jump();

    /*
    // Fiber initialization protocol
    {
      // allocateObject( FFI + function pointer ) call with fiber
      //caller.recv()
    }
    */
  }
}



// gns::FiberJump<int> value<T>()
gnsFiberCommand gnsFiberJump(gnsFiberTracker * tracker, gnsFiberCommand sendCmd) {
  // todo pop and push de fiber context in the thread local storage

  auto self = gnsFiberGetCurrent();

  gnsFiberContinuator selfContinuator;
                      selfContinuator.tracker = tracker;
  auto recvCmd = (gnsFiberCommand) setjmp(selfContinuator.jumpBuffer);

  //auto other =
  gnsFiberSetCurrent(self);
  /*
    puede utilizar self y other (fibers) para conocer el task
    o el memory manager, de forma que pueda traspasar el objeto de
    un fiber a otro, tambien puede saber si el objeto esta en la pila
  */

  if( recvCmd == GNS_FIBER_CALLTHROUGH ) {

    tracker->continuator->tracker->continuator = &selfContinuator;

    longjmp(tracker->continuator->jumpBuffer, sendCmd);
  }

  return recvCmd;
}
/*
swap fiber segments
*/


//int a_offset =



void gnsFiberStartup() {

  // inicializa los fiber locals, COMO?
  // entendiendo que ya se encuentra alojado el vector
  // locals[module]->section


}

void gnsFiberShutdown() {

}
