
cc_binary(
    name = "01",
    srcs = glob(["*.cpp", "*.h"]),
    deps = [
        "//utils:utils",
        "@bazel_tools//tools/cpp/runfiles",
    ],
    data = glob(["*.txt"] , exclude = ["CMakeLists.txt"])
)
