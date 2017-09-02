#pragma once
#include <gns/runtime/process.h>

#include "thread.hxx"

struct gnsProcess {
  const volatile gnsThread * mainThread;
};
