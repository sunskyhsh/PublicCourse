// Copyright @2018 Pony AI Inc. All rights reserved.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

int main() {
  cv::Mat image;
  // ATTENTION!!! : please use absolute path for reading the data file.
  image = imread("/home/sunsky/repo/PublicCourse/homework3/chessboard/chessboard_undistorted.png", CV_LOAD_IMAGE_COLOR);
  if (!image.data)        //判断图像载入是否成功  
  {  
    std::cout << "Fail to load image!!" << std::endl;  
    return 0;  
  }
  namedWindow("chessboard");
  imshow("chessboard", image);
  waitKey(0);
  // distort the image with k1 = 0.1, k2 = 0.1
  double k1 = 0.1;
  double k2 = 0.1;
  double cx = image.rows / 2;
  double cy = image.cols / 2;
  double fx = 500;
  double fy = 500;
  double nfx = 250;
  double nfy = 250;
  Mat dst = Mat(image.rows, image.cols, CV_8UC3, Scalar(0,0,0));
  for (int i=0; i<image.rows; i++) {
    for (int j=0; j<image.cols; j++) {
      double xp = (i - cx) / fx;
      double yp = (j - cy) / fy;
      double rs = xp*xp + yp*yp;
      int u = nfx * xp * (1 + k1 * rs + k2 * rs * rs) + cx;
      int v = nfy * yp * (1 + k1 * rs + k2 * rs * rs) + cy;
      dst.at<Vec3b>(u,v) = image.at<Vec3b>(i,j);      
    }
  }
  namedWindow("distorted chessboard");
  imshow("distorted chessboard", dst);
  waitKey(0);
  imwrite("/home/sunsky/repo/PublicCourse/homework3/chessboard/chessboard_distorted.png", dst);
  return 0;
}
