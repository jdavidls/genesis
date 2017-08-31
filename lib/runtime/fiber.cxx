#include <iostream>

#include <sys/mman.h>
#include <ucontext.h>
#include <setjmp.h>
#include <dlfcn.h>
#include <link.h>

#include <string.h>

#include <errno.h>

#include "fiber.hxx"

using namespace gns;

static void gnsFiberEntry(unsigned, unsigned);

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
  GNS_LOG(&selfContinuator);
    makecontext(&ucontext, (void(*)())&gnsFiberEntry, 2,
        (__uint32_t)((__uint64_t)&selfContinuator >> 32),
        (__uint32_t)((__uint64_t)&selfContinuator /*& 0xFFFFFFFF*/));

    setcontext(&ucontext);
  }

  return tracker;
}


int gnsFiberJump(gnsFiberTracker * tracker, int sendCmd) {
  gnsFiberContinuator selfContinuator;
  selfContinuator.tracker = tracker;

  auto recvCmd = setjmp(selfContinuator.jumpBuffer);

  if( recvCmd == GNS_FIBER_CALLTHROUGH ) {

    tracker->continuator->tracker->continuator = &selfContinuator;

    longjmp(tracker->continuator->jumpBuffer, sendCmd);
  }

  return recvCmd;
}

void gnsFiberEntry(unsigned _hi_bits, unsigned _lo_bits) {
  gnsFiberTracker tracker {
    /*.continuator = */(gnsFiberContinuator*) (
      ((__uint64_t)_hi_bits << 32) | ((__uint64_t)_lo_bits))
  };

  GNS_LOG(tracker.continuator);

  //gnsFiberSetInput()
  gnsFiberJump(&tracker, 1);

}



void gnsFiberStartup() {
  // inicializa los fiber locals, COMO?
  // establece

  // inicializa fiber memory manager (allocator)
  //gnsFiberContinue(gnsFiberCurrent);
/*
  if( setjmp(fiber.jumpBuffer) == 0 ) {
    auto yield = reinterpret_cast<gnsFiber*>(gnsFiberCurrent->dataBuffer.pointer);

    *yield = &fiber;

    GNS_LOG(gnsFiberCurrent);

    longjmp(gnsFiberCurrent->jumpBuffer, 1);
  }
*/
  // via FFI, via delegate, via xxx

}

void gnsFiberShutdown() {

}
