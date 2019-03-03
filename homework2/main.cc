// Copyright @2018 Pony AI Inc. All rights reserved.

#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

#include "homework2/pointcloud.h"
#include "homework2/separate_ground.h"

void cvtGray(const cv::Mat &image, cv::Mat &grayImage);
void laneDetect(cv::Mat &src);

int main() {
  // ATTENTION!!! : please use absolute path for reading the data file.
  const PointCloud pointcloud = ReadPointCloudFromTextFile(
      "/home/sunsky/repo/PublicCourse/homework2/sample_data/VelodyneDevice32c/0.txt");
  std::cout << "Total points read: " << pointcloud.points.size() << std::endl;
  std::cout << "Rotation: " << std::endl;
  std::cout << pointcloud.rotation << std::endl;
  std::cout << "Translation: " << std::endl;
  std::cout << pointcloud.translation.transpose() << std::endl;

  // Task 2: Separate the ground points from Pointcloud
  SeparateGround(pointcloud);
  std::cout << "Ground points separated." << std::endl;

  // Task 3: Image color manipulation
  cv::Mat image1, image2;
  // image 1
  image1 = cv::imread("/home/sunsky/repo/PublicCourse/homework2/sample_data/GigECameraDeviceTelephoto/0.jpg", 1);
  if (!image1.data)        //判断图像载入是否成功  
  {  
    std::cout << "Fail to load image!!" << std::endl;  
    return 0;  
  }  
  cv::Mat grayImage = cv::Mat::zeros(image1.rows, image1.cols, CV_8UC1);
  cvtGray(image1, grayImage);
  cv::imwrite("/home/sunsky/repo/PublicCourse/homework2/sample_data/GigECameraDeviceTelephoto/0_gray.jpg", grayImage);
  
  // image 2
  image2 = cv::imread("/home/sunsky/repo/PublicCourse/homework2/sample_data/GigECameraDeviceWideAngle/0.jpg", 1);
  if (!image2.data)        //判断图像载入是否成功  
  {  
    std::cout << "Fail to load image!!" << std::endl;  
    return 0;  
  }
  grayImage = cv::Mat::zeros(image2.rows, image2.cols, CV_8UC1);
  cvtGray(image2, grayImage);
  cv::imwrite("/home/sunsky/repo/PublicCourse/homework2/sample_data/GigECameraDeviceWideAngle/0_gray.jpg", grayImage);
  std::cout << "Image has been turned into gray." << std::endl;

  // Task 4: Lane boundary detection
  laneDetect(image1);
  cv::imwrite("/home/sunsky/repo/PublicCourse/homework2/sample_data/GigECameraDeviceTelephoto/output.jpg", image1);
  laneDetect(image2);
  cv::imwrite("/home/sunsky/repo/PublicCourse/homework2/sample_data/GigECameraDeviceWideAngle/output.jpg", image2);

  return 0;
}

void cvtGray(const cv::Mat &image, cv::Mat &grayImage) {
  for (int i=0; i<image.rows; i++) {
    for (int j=0; j<image.cols; j++) {
      grayImage.at<uchar>(i,j) = (4898*image.at<cv::Vec3b>(i,j)[2] + \
        9618*image.at<cv::Vec3b>(i,j)[1] + 1868*image.at<cv::Vec3b>(i,j)[0] + 50) >> 14;
    }
  }
}

void laneDetect(cv::Mat &src) {
  std::cout << "read ok." << std::endl;
  if (!src.data)        //判断图像载入是否成功  
  {  
    std::cout << "Fail to load image!!" << std::endl;  
    return;  
  }
  cv::Mat detected_edges, src_gray = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
  cvtGray(src, src_gray);
  cv::blur(src_gray, detected_edges, cv::Size(5,5));
  int canny_low_thresh = 50;
  int canny_high_thresh = 150;
  int canny_size = 3;
  int hough_rho = 1;
  float hough_theta = 0.0175;
  int hough_thresh = 15;
  int hough_min_length = 100;
  int hough_max_gap = 40;
  cv::Canny(detected_edges, detected_edges, canny_low_thresh, canny_high_thresh, canny_size);
  std::vector<cv::Vec4i> lines, final_lines;
  cv::Point root_points[1][4];
  root_points[0][0] = cv::Point(0, 0);
  root_points[0][1] = cv::Point(src.cols, 0);
  root_points[0][2] = cv::Point(src.cols, src.rows / 5 * 3);
  root_points[0][3] = cv::Point(0, src.rows / 5 * 3);
  const cv::Point* ppt[1] = {root_points[0]};
  int npt[] = { 4 };
  cv::fillPoly(detected_edges, ppt, npt, 1, cv::Scalar(0,0,0));
  cv::HoughLinesP(detected_edges, lines, hough_rho, hough_theta, \
    hough_thresh, hough_min_length, hough_max_gap);
  for (int i=0; i<lines.size(); i++) {
    if (abs(lines[i][0] - lines[i][2]) < 2) {
      final_lines.push_back(lines[i]);
    }
    else if (fabs((lines[i][1] - lines[i][3]) / (lines[i][0] - lines[i][2])) > 0.2) {
      final_lines.push_back(lines[i]);
    }
  }
  cv::Mat line_img = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
  for (int i=0; i<final_lines.size(); i++) {
    cv::line(line_img, cv::Point(final_lines[i][0], final_lines[i][1]), cv::Point(final_lines[i][2], final_lines[i][3]), cv::Scalar(0,0,255), 8);
  }
  cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
  cv::addWeighted(src, 0.8, line_img, 1.0, 0.0, dst);  
}
