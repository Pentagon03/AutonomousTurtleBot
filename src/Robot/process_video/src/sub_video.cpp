//node : sub_video
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include <std_msgs/UInt8MultiArray.h>
using namespace cv;
using namespace std;
void imageCallback(const std_msgs::UInt8MultiArray::ConstPtr& array)
{
  try
  {
    Mat frame = imdecode(array->data, 1);
    imshow("view", frame);
    /*
    //frame의 속성을 변환
    vector<Mat> ch; 
    split(frame,ch);
    ch[1]=0;
    Mat mgd;
    merge(ch,mgd);
    imshow("what",mgd);
    */
    waitKey(10);
  }

  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cannot decode image");
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sub_video");

  // cv::namedWindow("view");
  // cv::startWindowThread();

  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("mat_msg", 100, imageCallback);

  ros::spin();
  destroyWindow("view");
}