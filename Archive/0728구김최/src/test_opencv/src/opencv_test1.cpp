#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "opencv_test1");   
  cv::VideoCapture cap(0);               
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
  cv::Mat frame;

  while (1) {
    cap >> frame;
    if(!frame.empty()) {
      cv::imshow("cam",frame);
      if(cv::waitKey(10)==27) break; //ESC 누르면 종료
    }
  }
  cv::destroyAllWindows();
  return 0;
}

