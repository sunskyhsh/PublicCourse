#include <iostream>
#include <fstream>
#include "homework2/pointcloud.h"
#include "homework2/separate_ground.h"
#include <glog/logging.h>

int SeparateGround(const PointCloud& pointcloud) {

  std::ofstream file;
  file.open("/home/sunsky/repo/PublicCourse/homework2/points_without_ground.txt");
  // CHECK(file.is_open()) << "Fail to open file!\n";

  file << pointcloud.translation(0) << "," << pointcloud.translation(1) << "," << pointcloud.translation(2) << "\n";
  file << pointcloud.rotation(0,0) << "," << pointcloud.rotation(0,1) << "," << pointcloud.rotation(0,2) << "\n" ;
  file << pointcloud.rotation(1,0) << "," << pointcloud.rotation(1,1) << "," << pointcloud.rotation(1,2) << "\n" ;
  file << pointcloud.rotation(2,0) << "," << pointcloud.rotation(2,1) << "," << pointcloud.rotation(2,2) << "\n" ;
  for (int i=0; i<pointcloud.points.size(); i++) {
    if (pointcloud.points[i](2) < -1.5)
      continue;
    file << i << "," << pointcloud.points[i](0) << "," << pointcloud.points[i](1) << "," << pointcloud.points[i](2) << "\n";
  }
  file.close();
  std::cout << "Write file finished." << std::endl;
  return 0;
}
