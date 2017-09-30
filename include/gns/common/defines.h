#pragma once


# define GNS_ARCH_BITS ( sizeof(void*) * 8 )

//#define GNS_TEXT(S) { { GNS_C_ARRAY_LENGTH(S) - 1 }, S }

#ifdef __cplusplus
# define GNS_SYMBOL_C(SYMBOL) :: gns ## SYMBOL
# define GNS_SYMBOL_CXX(SYMBOL) :: gns :: SYMBOL
# define GNS_SYMBOL(SYMBOL) GNS_SYMBOL_CXX(SYMBOL)
#else
# define GNS_SYMBOL_C(SYMBOL) gns ## SYMBOL
# define GNS_SYMBOL(SYMBOL) GNS_SYMBOL_C(SYMBOL)
#endif

#ifdef __cplusplus
# define GNS_C_LINKAGE_BEGIN extern "C" {
# define GNS_C_LINKAGE_END }
# define GNS_CXX_NAMESPACE(...) namespace gns { __VA_ARGS__ }
# define GNS_C_LINKAGE(...) extern "C" { __VA_ARGS__ }
# define GNS_CODE_C(...) extern "C" { __VA_ARGS__ }
# define GNS_CODE_CXX(...) namespace gns { __VA_ARGS__ }
#else
# define GNS_C_LINKAGE_BEGIN
# define GNS_C_LINKAGE_END
# define GNS_C_LINKAGE(...) __VA_ARGS__
# define GNS_CXX_NAMESPACE(...)
# define GNS_CODE_C(...) __VA_ARGS__
# define GNS_CODE_CXX(...)
#endif

#ifdef __cplusplus
# define GNS_THREAD_LOCAL thread_local
#else
# define GNS_THREAD_LOCAL _Thread_local
#endif


#ifdef __cplusplus
# define GNS_ASSERT(...)                                                      \
  for(; !(__VA_ARGS__); (std::cerr << "Assertion: " #__VA_ARGS__ << std::endl), std::abort() )

//# define GNS_ASSERT(...) ((void) __VA_ARGS__)                               \

#else
# define GNS_ASSERT(...)                                                      \
  for(; !(__VA_ARGS__);, _abort() )
#endif


#ifndef __cplusplus
# define GNS_STATIC_ASSERT(MSG, ...)                                          \
    _Static_assert(__VA_ARGS__, MSG "\n" #__VA_ARGS__)
#else
# define GNS_STATIC_ASSERT(MSG, ...)                                          \
    static_assert(__VA_ARGS__, MSG "\n" #__VA_ARGS__)
#endif



#ifdef __cplusplus
#define GNS_LOG(EXPR) ( std::cout << (#EXPR) << " = " << (EXPR) << std::endl )
#else
#define GNS_LOG(EXPR)
#endif


#ifdef __cplusplus
# define GNS_DECLARE_NON_COPYABLE(typeName)                                         \
    typeName (const typeName&) = delete;                                            \
    typeName& operator= (const typeName&) = delete;
#endif























#define GNS_CHECK_COMPAT(TypeName)                                            \
  GNS_CODE_CXX(                                                               \
    GNS_STATIC_ASSERT(                                                        \
      "GNS C/C++ compatibility error, size of type " # TypeName " missmach",  \
      sizeof(GNS_SYMBOL_C(TypeName)) == sizeof(GNS_SYMBOL_CXX(TypeName))      \
    );                                                                        \
  )


#define $_HEAD($, ...) $
#define $_BODY($, ...) __VA_ARGS__



#define GNS_FORWARD_DECLARE(TupleTypeName, ...)                               \
  GNS_CODE_C(                                                                 \
    $_HEAD(__VA_ARGS__) gns ## TupleTypeName;                                 \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    $_BODY(__VA_ARGS__)                                                       \
    $_HEAD(__VA_ARGS__) TupleTypeName;                                        \
  )


#define GNS_TYPEALIAS_DECLARE(TypeName, ...)                                  \
  GNS_CODE_C(                                                                 \
    typedef __VA_ARGS__ gns ## TypeName;                                      \
  )                                                                           \
  GNS_CODE_CXX(                                                               \
    using TypeName = GNS_SYMBOL_C(TypeName);                                  \
  )                                                                           \
  GNS_CHECK_COMPAT(TypeName)


#ifdef __cplusplus
# define GNS_DECLARE_NON_COPYABLE(TypeName)                                   \
    TypeName (const TypeName&) = delete;                                      \
    TypeName& operator= (const TypeName&) = delete;

# define GNS_DECLARE_C_COMPAT(TypeName)                                       \
    TypeName(const GNS_SYMBOL_C(TypeName)& init) {                            \
      GNS_STATIC_ASSERT(                                                        \
        "GNS C/C++ compatibility error, size of type " # TypeName " missmach",  \
        sizeof(GNS_SYMBOL_C(TypeName)) == sizeof(GNS_SYMBOL_CXX(TypeName))      \
      );                                                                        \
      *reinterpret_cast<GNS_SYMBOL_C(TypeName)*>(this) = init;                \
    }                                                                         \
    operator GNS_SYMBOL_C(TypeName)& () {                                     \
      return *reinterpret_cast<GNS_SYMBOL_C(TypeName)*>(this);                \
    }                                                                         \
    operator const GNS_SYMBOL_C(TypeName)& () const {                         \
      return *reinterpret_cast<const GNS_SYMBOL_C(TypeName)*>(this);          \
    }
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

#define GNS_ATTR_ALIAS(ALIAS)                                                       \
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
