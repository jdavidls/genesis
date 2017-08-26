C_STD = '--std=c++17'


cc_library(
    name = "gns-common",
    srcs = glob(['lib/common/**/*.c', 'lib/common/**/*.cxx']),
    hdrs = glob(['include/gns/common/**/*.h']),
    copts=[C_STD],
    linkopts=[],
    includes=['include']
)

cc_library(
    name = "gns-runtime",
    srcs = glob(['lib/runtime/**/*.c', 'lib/runtime/**/*.cxx']),
    hdrs = glob(['include/gns/common/**/*.h', 'include/gns/runtime/**/*.h']),
    copts=[C_STD],
    linkopts=[],
    includes=['include'],
    deps = [
        'gns-common'
    ]

)

cc_library(
    name = "gns-core",
    srcs = glob(['lib/core/**/*.c', 'lib/core/**/*.cxx']),
    hdrs = glob(['include/gns/core/**/*.h']),
    copts=[C_STD],
    linkopts=[],
    includes=['include'],
    deps = [
        'gns-common',
        'gns-runtime'
    ]
)


cc_binary(
    name = "gns",
    srcs = glob(['bin/gns/**/*.cxx', 'bin/gns/**/*.c', 'include/**/*.h']),
    copts=['--std=c++17'],
    includes=['include'],
    deps = [
      'gns-common',
      'gns-runtime',

    ]
)
