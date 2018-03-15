# Homework3

Now, you guys have been familiar with pointcloud data and have learnt about calibrations. Let's implement something cool.

## New dependency: opencv

[opencv](https://opencv.org/) is a package for image processing. It provides useful computation utilities and display functions. An example is provided under the chessboard folder. It will be used in problem 2 & 3 in this homework. **Note: you will need to install OpenCV yourself following [this tutorial](https://docs.opencv.org/trunk/d7/d9f/tutorial_linux_install.html).**

## Homework

### 1. Get familiar with transformation representation.
When we want to rotate something in 3D space, we have many representations for the rotation. For example, roll-pitch-yaw is intuitive and used in airplanes; angle-axis is intuitive and clean, and rotation matrix is easy to use in computation. Among these three, rotation matrix is typically not easy for people to imagine. However, if you convert it to another format, you would be clear what it means.

Your task is to implement the conversion from rotation matrix to roll-pitch-yaw and angle-axis representations. For roll-pitch-yaw representation, the rotation intrinsic is roll->pitch->yaw. That is, the rotation sequence is **R(yaw) * R(pitch) * R(roll)**.

**What to submit:** Your C++ implementation of rotation/rotation_test.cc to pass the unit tests non-trivially.

### 2. Chessboard distortion

Chessboard is commonly used in camera calibration. Before calibration, the photo on the chessboard has some distortions like shown in the [chessboard/chessboard.png](https://github.com/ponyai/PublicCourseInternalReview/blob/master/homework3/chessboard/chessboard.png). Getting the intrinsic parameters is complex. However, if you have the intrinsic parameters, you could get a distorted image easily.

Your task is as follows:
- Load chessboard/chessboard_undistorted.png.
- Apply only radial distortion with k1 = 0.1 and k2 = 0.1 on it. For details distortion model, please refer to [this tutorial](https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html).
- Output the distorted image.

**What to submit:** Your C++ code to generate chessboard and distorted image, and both images.

### 3. Ground detection (**Open-ended task**)
In homework2, we provided some frames of [pointcloud](https://github.com/ponyai/PublicCourseInternalReview/blob/master/homework2/sample_data.tar.gz) and [a picture for ground points](https://github.com/ponyai/PublicCourseInternalReview/blob/master/homework2/ground_only.png).
Actually, the picture was trivially generated from existing detected ground.
It is hard to generate ground from single frame 32c Lidar data.
Detecting ground typically requires multiple frames to be accurate.

Your task is to detect the ground based on multiple frames.
This could be done by the following three steps.
- convert the pointclouds of multiple continuous frames to world coordinate system.
- get the ground according to the method taught in class.
- outputs the result using OpenCV or other proper tools. The result should contain only overlaid ground points from the 100 frames and display in world coordinate system.

**What to submit:** Your C++ code to generate the ground points.