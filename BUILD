##
##
##

C_STD = '--std=c++17'

SYS_LIBS = ['-lrt', '-ldl', '-lpthread', '-lm']

LLVM_LIBS = ['-L/usr/local/lib', '-lLLVM-6.0svn']

LLVM_COPTS = [
    '-I/usr/local/include',
    '-pedantic',
    #'-std=c++11',
    '-fPIC',
    '-fvisibility-inlines-hidden',
    '-fno-exceptions',
    '-fno-rtti',
    '-g',
    '-W',
    '-Werror=date-time',
    '-Wall',
    '-Wno-unused-parameter',
    '-Wwrite-strings',
    '-Wcast-qual',
    '-Wno-missing-field-initializers',
    '-Wno-long-long',
    '-Wno-maybe-uninitialized',
    '-Wdelete-non-virtual-dtor',
    '-Wno-comment',
]

LLVM_DEFS = [
  '-D_GNU_SOURCE',
  '-D_DEBUG',
  '-D__STDC_CONSTANT_MACROS',
  '-D__STDC_FORMAT_MACROS',
  '-D__STDC_LIMIT_MACROS'
]
'''
cc_library(
    name = "gns-common",
    srcs = glob(['lib/common/**/*.hxx', 'lib/common/**/*.cxx']),
    hdrs = glob(['include/gns/common/**/*.h']),
    copts=[C_STD],
    linkopts=SYS_LIBS + [],
    includes=['include']
)

cc_library(
    name = "gns-runtime",
    srcs = glob(['lib/runtime/**/*.hxx', 'lib/runtime/**/*.cxx']),
    hdrs = glob(['include/**/*.h']),
    copts=[C_STD],
    linkopts=SYS_LIBS + [],
    includes=['include'],
    deps = []
)

cc_library(
    name = "gns-core",
    srcs = glob(['lib/core/**/*.hxx', 'lib/core/**/*.cxx']),
    hdrs = glob(['include/**/*.h']),
    copts=[C_STD] + LLVM_COPTS,
    linkopts=SYS_LIBS + LLVM_LIBS,
    includes=['include'],
    deps = [ ]
)
'''


cc_binary(
    name = "gns",
    srcs = glob(['include/**/*.h']) +
           glob(['bin/gns/**/*.cxx', 'bin/gns/**/*.hxx']) +
           glob(['lib/**/*.cxx', 'lib/**/*.hxx']),

    includes=['include'],
    #defines=LLVM_DEFS,
    copts=[C_STD] + LLVM_COPTS,
    linkopts=SYS_LIBS + LLVM_LIBS ,

)
