#pragma once


#ifdef __cplusplus
# define GNS_C_LINKAGE extern "C"
# define GNS_C_LINKAGE_BEGIN GNS_C_LINKAGE {
# define GNS_C_LINKAGE_END }
#else
# define GNS_C_LINKAGE extern
# define GNS_C_LINKAGE_BEGIN
# define GNS_C_LINKAGE_END
#endif


#ifdef __cplusplus
# define GNS_THREAD_LOCAL thread_local
#else
# define GNS_THREAD_LOCAL _Thread_local
#endif

#ifdef __cplusplus
# define GNS_ASSERT(...)                                                            \
  for(; !(__VA_ARGS__); (std::cerr << "Assertion: " #__VA_ARGS__ << std::endl), std::abort() )
#else
# define GNS_ASSERT(...)                                                            \
  for(; !(__VA_ARGS__);, _abort() )
#endif


#ifndef __cplusplus
# define GNS_STATIC_ASSERT(...)                                                     \
    _Static_assert(__VA_ARGS__, #__VA_ARGS__)
#else
# define GNS_STATIC_ASSERT(...)                                                     \
    static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif



#ifdef __cplusplus
#define GNS_LOG(EXPR) ( std::cout << (#EXPR) << " = " << (EXPR) << std::endl )
#else
#define GNS_LOG(EXPR)
#endif




//#ifdef __cplusplus

// ATTRIBUTES
// BUG: atencion attributos no son posibles en C
#define GNS_ATTR_USED                                                               \
  [[ gnu::used ]]

#define GNS_ATTR_NO_INLINE                                                          \
  [[ gnu::noinline ]]

#define GNS_ATTR_SECTION(SECTION_NAME)                                              \
  [[ gnu::section( # SECTION_NAME ) ]]

#define GNS_ATTR_ALIAS(ALIAS)                                                 \
  [[ gnu::alias( # ALIAS ) ]]

// GNU SECTION_SUPPORT
#define GNS_SECTION_DECLARE(SECTION_NAME)                                           \
  extern gnsByte __start_ ## SECTION_NAME;                                          \
  extern gnsByte __stop_ ## SECTION_NAME

#define GNS_SECTION_START(SECTION_NAME)                                             \
  ((size_t)& __start_ ## SECTION_NAME)

#define GNS_SECTION_END(SECTION_NAME)                                               \
  ((size_t)& __stop_ ## SECTION_NAME)

#define GNS_SECTION_SIZE(SECTION_NAME) (                                            \
  GNS_SECTION_END(SECTION_NAME) - GNS_SECTION_START(SECTION_NAME)                   \
)

#define GNS_SECTION_OFFSET_OF(SECTION_NAME, VAR) (                                  \
  ((size_t)(VAR)) - GNS_SECTION_START(SECTION_NAME)                                 \
)

#define GNS_SECTION_CONTAINS(SECTION_NAME, VAR) (                                   \
  ((size_t)(VAR)) >= GNS_SECTION_START(SECTION_NAME)  &&                            \
  ((size_t)(VAR)) < GNS_SECTION_END(SECTION_NAME)                                   \
)



//
