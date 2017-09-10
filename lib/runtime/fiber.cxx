#include <iostream>
#include <utility>


#include <sys/mman.h>
#include <ucontext.h>
#include <setjmp.h>
#include <string.h>
#include <errno.h>

#include "fiber.hxx"

using namespace gns;

enum gnsFiberCommand {

  GNS_FIBER_SWAP = 1,
  GNS_FIBER_DEALLOCATE = 2,

  //GNS_FIBER_CALLTHROUGH = 0,
};

struct ThreadLocalStorage {
  Fiber* fiber;

  // SWAP
  FiberContinuator* continuator;



};

static thread_local ThreadLocalStorage threadLocalStorage = {};

static void gnsFiberEntry();
static ThreadLocalStorage * getTLS();

 // proces global constants var.
static Natural pageLength = 4096;
static Natural stackLength = 1*1016*1024;


/*
template<>
  Array<Global<GNS_GLOBAL_SCOPE_FIBER, void>*>
    GlobalManager<GNS_GLOBAL_SCOPE_FIBER>::globals{};
*/


/*
void* gnsFiberGlobalLookup(gnsGlobal* global) {
  auto& manager = __currentFiber->globalManager;
  return manager.lookup(*global);
}
*/



gnsFiber * gnsFiberGetCurrent() {
  return threadLocalStorage.fiber;
}

gnsFiberContinuator* gnsFiberAllocate() {

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

  FiberContinuator self = { threadLocalStorage.fiber };

  do {

    if( setjmp(self.jumpBuffer) == 0 ) {
      ucontext_t ucontext;
      GNS_ASSERT( getcontext(&ucontext) == 0 ); // esto puede ser cacheado.

      ucontext.uc_stack.ss_sp = stack + pageLength;
      ucontext.uc_stack.ss_size = stackLength;
      ucontext.uc_link = nullptr; // TODO vincular a un recoletor de fibers.

      threadLocalStorage.continuator = &self;
      //__fiberInit.stack = { { stackLength }, stack };

      makecontext(&ucontext, (void(*)())&gnsFiberEntry, 0);
      setcontext(&ucontext);
    }

  }
  while(false);

  threadLocalStorage.fiber = self.fiber;

  return threadLocalStorage.continuator;
}

/*
  IDEA debe almacenar el continuador en la estancia del fiber, para poder
  realizar un retorno en caso de que el fiber llamado no devuelva el control.
*/

// SAFE TLS getter for thread swap
[[gnu::noinline()]]
static ThreadLocalStorage * getTLS() {
  return &threadLocalStorage;
}

gnsFiberContinuator * gnsFiberSwap(gnsFiberContinuator * c_other) {
  auto other = reinterpret_cast<FiberContinuator*>(c_other);

  auto prevTLS = getTLS();
  FiberContinuator self = { prevTLS->fiber };
  int recvCommand;

  // adquiere el mutex del fiber al que va a saltar

  do {

    recvCommand = setjmp(self.jumpBuffer);
    if ( recvCommand == 0 ) {
      prevTLS->continuator = &self;
      longjmp(other->jumpBuffer, 1);
    }

  }
  while(false);

  // libera el mutex del fiber que le ha devuelto el control

  auto postTLS = getTLS();

  auto callerFiber = postTLS->fiber;
  auto callerContinuator = postTLS->continuator;
  postTLS->fiber = self.fiber;

  if( prevTLS != postTLS ) {
    // thread swap detected
  }

  return callerContinuator;
}


void gnsFiberEntry() {
  Fiber self;

  gnsFiberStartup(&self);

  FiberTracker owner( std::move(getTLS()->continuator) );

  GNS_LOG(owner.continuator);

  do {

    /*
    // Fiber initialization protocol
    {
      // allocateObject( FFI + function pointer ) call with fiber
      //caller.recv()
    }
    */

    owner.swap();

  }
  while(false);
  //while(fiber.keepAlive);

  gnsFiberShutdown(&self);

  // salta al owner, con un comando DEALLOCATE (que),
  getTLS()->continuator = nullptr; // TERMINATE SIGNAL
  longjmp(owner.continuator->jumpBuffer, 1);
}


void gnsFiberStartup(gnsFiber* c_fiber) {
  auto fiber = reinterpret_cast<Fiber*>(c_fiber);

  threadLocalStorage.fiber = fiber;
}

void gnsFiberShutdown(gnsFiber* self) {

}
