#pragma once
#include <gns/runtime/process.h>

#include "thread.hxx"

struct gnsProcessStructure {
  gnsThread mainThread;
};

extern gnsProcessStructure gnsProcessInstance;
