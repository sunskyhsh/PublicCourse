#include "homework2/pointcloud.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
  const int SIDE = 1600;
  const double RESOLUTION = 0.5;
  const double INF = 9999;
  const int MIN_NUMBER = 200;
  const double GROUND_THRESH = 0.5;
  Mat world_height = Mat::ones(SIDE,SIDE,CV_64FC1);
  for (int i=0; i<SIDE; i++) {
    for (int j=0; j<SIDE; j++) {
      world_height.at<double>(i,j) = INF;
    }
  }
  cout << "World initialized. Constructing..." << endl;
  for (int i=0; i<200; i++) {
    PointCloud pointcloud = ReadPointCloudFromTextFile(
      "/home/sunsky/pony_data/VelodyneDevice32c/"+std::to_string(i)+".txt");
    if ((i%20) == 0) cout << "progress: " << i << "/200" << endl;
    int points_size = pointcloud.points.size();
    for (int j=0; j<points_size; j++) {
      Eigen::Vector3d point = pointcloud.rotation * pointcloud.points[j] + pointcloud.translation;
      int x = (point.x()+700) / RESOLUTION;
      int y = (point.y()-400) / RESOLUTION;
      if (x>=0 && x<SIDE && y>=0 && y<SIDE) {
        world_height.at<double>(x,y) = point.z();
      }
    }
  }
  cout << "World constructed. Detecting ground..." << endl;
  Mat mat_tmp =  world_height.clone();
  int* mat_begin = mat_tmp.ptr<int>(0);
  int* mat_end = mat_tmp.ptr<int>(SIDE-1);
  sort(mat_begin, mat_end);
  double sum_tmp = 0;
  for (int i=0; i<MIN_NUMBER; i++) {
    sum_tmp += mat_tmp.at<double>(i);
  }
  double min_height = sum_tmp / MIN_NUMBER;
  cout << "Ground detected. Rendering image..." << endl;
  Mat ground_image = Mat(SIDE, SIDE, CV_8UC3, Scalar(0,0,0));
  for (int i=0; i<SIDE; i++) {
    for (int j=0; j<SIDE; j++) {
      if (world_height.at<double>(i,j) < min_height + GROUND_THRESH) {
        ground_image.at<Vec3b>(i,j) = Vec3b(80,220,40);
      }
      else if (world_height.at<double>(i,j) != INF) {
        ground_image.at<Vec3b>(i,j) = Vec3b(220,80,0);
      }
    }
  }
  imwrite("/home/sunsky/repo/PublicCourse/homework3/ground/ground image.jpg", ground_image);
  imshow("ground image", ground_image);
  waitKey(0);
  return 0;
}