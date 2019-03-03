// Copyright @2018 Pony AI Inc. All rights reserved.

#include "homework3/rotation/rotation.h"
#include <cmath>

namespace homework3 {

Eigen::Vector3d ToRollPitchYaw(Eigen::Matrix3d rotation) {
  Eigen::Vector3d rollpitchyaw;
  double cosy = sqrt(rotation(0,0)*rotation(0,0) + rotation(1,0)*rotation(1,0));
  if (cosy < 1e-6) {
    rollpitchyaw(2) = atan2f(-rotation(1,2), rotation(1,1));
    rollpitchyaw(1) = atan2f(-rotation(2,0), cosy);
    rollpitchyaw(0) = 0;
  }
  else {
    rollpitchyaw(2) = atan2f(rotation(2,1), rotation(2,2));
    rollpitchyaw(1) = atan2f(-rotation(2,0), cosy);
    rollpitchyaw(0) = atan2f(rotation(1,0), rotation(0,0));
  }
  return rollpitchyaw;
}

Eigen::AngleAxisd ToAngleAxis(Eigen::Matrix3d rotation) {
  double theta = acosf((rotation(0,0)+rotation(1,1)+rotation(2,2)-1) / 2);
  double rx = (rotation(2,1) - rotation(1,2) / 2 / sin(theta));
  double ry = (rotation(0,2) - rotation(2,0) / 2 / sin(theta));
  double rz = (rotation(1,0) - rotation(0,1) / 2 / sin(theta));
  return Eigen::AngleAxisd(theta, Eigen::Vector3d(rx, ry, rz));
}
}  // namespace homework3
