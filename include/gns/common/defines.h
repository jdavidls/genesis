/* -*- C++ -*- */
#pragma once

#define GNS_ASSERT(EXPR) \
  for(; !(EXPR); (std::cerr << "Assertion: " #EXPR << std::endl), std::abort() )

#define GNS_GLOBAL  __attribute__ ((visibility ("default")))
#define GNS_LOCAL   __attribute__ ((visibility ("hidden")))

#define GNS_FIBER_LOCAL __attribute((section("gnsfls")))
#define GNS_NO_STRIP __attribute((used))

#ifdef __cplusplus
#define GNS_C_LINKAGE extern "C"
#define GNS_C_LINKAGE_BEGIN GNS_C_LINKAGE {
#define GNS_C_LINKAGE_END }
#define GNS_THREAD_LOCAL thread_local
#define GNS_LOG(EXPR) \
  ( std::cout << (#EXPR) << " = " << (EXPR) << std::endl )
#else
#define GNS_C_LINKAGE extern
#define GNS_C_LINKAGE_BEGIN
#define GNS_C_LINKAGE_END
#define GNS_THREAD_LOCAL _Thread_local
#endif

#define GNS_C_ARRAY_LENGTH(X) \
  ( sizeof(X) / sizeof(*(X)) )

#define GNS_ARRAY_TYPE(TYPE, RANK)      \
struct {                                \
  gnsNatural extent[RANK];              \
  TYPE * pointer;                       \
}

#define GNS_ARRAY_RANK(ARRAY) GNS_C_ARRAY_LENGTH( (ARRAY).extent);
