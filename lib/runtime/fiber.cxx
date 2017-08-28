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

GNS_LOCAL thread_local gnsFiber gnsCurrentFiber = nullptr;


static void gnsFiberTrampoline();

gnsFiber gnsFiberAllocate() {

  Natural pageLength = 4096; // proces global var.
  Natural stackLength = 1*1016*1024;

  gnsFiber fiber;

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


  GNS_LOG(gnsCurrentFiber);
  gnsCurrentFiber->dataBuffer.pointer = &fiber;
  gnsCurrentFiber->dataBuffer.length = sizeof(fiber);

  ucontext_t ucontext;

  GNS_ASSERT( getcontext(&ucontext) != -1 );

  ucontext.uc_stack.ss_sp = stack + pageLength;
  ucontext.uc_stack.ss_size = stackLength;
  ucontext.uc_link = nullptr; // TODO vincular a un recoletor de fibers.

  makecontext(&ucontext, &gnsFiberTrampoline, 0);

  if( setjmp(gnsCurrentFiber->jumpBuffer) == 0 )
    setcontext(&ucontext);

  return fiber;
}

void gnsFiberDeallocate(gnsFiber* fiber) {

}

void gnsFiberTrampoline() {
  // 64 bytes align
  gnsFiberStructure fiber; // yield to

  // inicializa fiber memory manager (allocator)
  //gnsFiberContinue(gnsCurrentFiber);

  if( setjmp(fiber.jumpBuffer) == 0 ) {
    auto yield = reinterpret_cast<gnsFiber*>(gnsCurrentFiber->dataBuffer.pointer);

    *yield = &fiber;

    GNS_LOG(gnsCurrentFiber);

    longjmp(gnsCurrentFiber->jumpBuffer, 1);
  }

  // via FFI, via delegate, via xxx

  //gnsFiberStartup();
  //do the work
  //gnsFiberShutdown();


}

/*
#define fiberContinue(fiber, command)
do {
  auto self = gnsCurrentFiber;
  auto cmd = setjmp(self->jumpBuffer);
  if( cmd == 0)
    longjmp((fiber)->jumpBuffer);

  // th thread can change here
} while(0)
*/

Fiber::Command gnsFiberContinue(gnsFiber fiber, Fiber::Command sendCommand) {
  auto self = gnsCurrentFiber;

  // TODO establecer el buffer de entrada
  //self->dataBuffer.pointer = nullptr;
  //self->dataBuffer.length = 0;

  auto recvCommand = setjmp(self->jumpBuffer);
  if( recvCommand == 0 )
    longjmp(fiber->jumpBuffer, sendCommand);


  // can store gnsCurrentFiber, the caller fiber in a yield channel

  gnsCurrentFiber = self;
/*
  // talvez los comandos deban ser flags
  // el flag throw lanza una exccepcion (el flag mas elevado)
  // el flag callthrough

  //else if(recvCommand & Fiber::Command::THROW )

  switch( recvCommand ) {

    case Fiber::Command::CALLTHROUGH: {

      break;
    }

    case Fiber::Command::THROW: {
      gnsCurrentFiber = self;
      throw nullptr; // throw a gns::Object from input data..
    }

    default: {
      gnsCurrentFiber = self;
      break;
    }

  }

  //
*/
  return recvCommand;
}


void gnsFiberStartup() {
  // inicializa los fiber locals, COMO?
  // establece
}

void gnsFiberShutdown() {

}

void gnsFiberContinue(gnsFiber* fiber) {

}

void gnsFiberRaise(gnsFiber* fiber) {

}
