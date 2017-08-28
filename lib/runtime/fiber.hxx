#pragma once
#include <setjmp.h>

#include <gns/runtime/fiber.h>


struct alignas(64) gnsFiberStructure {

  struct {
    void* pointer;
    gns::Natural length;
  } dataBuffer;

  jmp_buf jumpBuffer;

  gnsFiber yieldTo[1];
};

extern thread_local gnsFiber gnsCurrentFiber;
