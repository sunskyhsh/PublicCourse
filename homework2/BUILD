package(default_visibility = ["//visibility:public"])

cc_library(
    name = "pointcloud",
    srcs = ["pointcloud.cc"],
    hdrs = ["pointcloud.h"],
    deps = [
        "@eigen//:eigen",
        "@glog//:glog",
    ],
)

cc_library(
    name = "separate_ground",
    srcs = ["separate_ground.cc"],
    hdrs = ["separate_ground.h"],
    deps = [
        "@eigen//:eigen",
        "@glog//:glog",
        ":pointcloud",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "@opencv//:core",
        "@opencv//:highgui",
        "@opencv//:imgproc",
        "@opencv//:imgcodecs",
        ":pointcloud",
        ":separate_ground",
    ],
)
