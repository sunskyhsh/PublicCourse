#include "Eigen/Core"
#include "Eigen/Geometry"
#include <iostream>
#include "homework3/rotation/rotation.h"

int main() {
  Eigen::Matrix3d rotation;
  std::cout << "BasicTest:" << std::endl;
  rotation << 1, 0, 0,
              0, 1, 0,
              0, 0, 1;
  auto roll_pitch_yaw = homework3::ToRollPitchYaw(rotation);
  auto angle_axis = homework3::ToAngleAxis(rotation);
  std::cout << roll_pitch_yaw << std::endl;
  std::cout << "====" << std::endl;
  std::cout << angle_axis.angle() << ", " << angle_axis.axis().x() << ", "
  << angle_axis.axis().y() << ", " << angle_axis.axis().z() << std::endl;
  std::cout << "====" << std::endl;

  std::cout << "RollPitchYawTest:" << std::endl;
  rotation << 0.97517033, -0.153792, -0.15934508,
              0.0978434, 0.94470249, -0.31299183,
              0.19866933, 0.28962948, 0.93629336;
  roll_pitch_yaw = homework3::ToRollPitchYaw(rotation);
  std::cout << roll_pitch_yaw << std::endl;
  std::cout << "====" << std::endl;

  std::cout << "AngleAxisTest:" << std::endl;
  rotation << 0.99934681, -0.03017958, 0.0199023,
              0.02997888, 0.99949734, 0.01032745,
              -0.02020334, -0.00972537, 0.99974821;
  angle_axis = homework3::ToAngleAxis(rotation);  
  std::cout << angle_axis.angle() << ", " << angle_axis.axis().x() << ", "
  << angle_axis.axis().y() << ", " << angle_axis.axis().z() << std::endl;
  std::cout << "====" << std::endl;
  return 0;
}
