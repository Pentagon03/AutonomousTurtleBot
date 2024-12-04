//node : sub_video
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include <std_msgs/UInt8MultiArray.h>
using namespace cv;
using namespace std;
time_t start;
void change_hval(Mat&frame){
    vector<Mat> ch; 
    split(frame,ch);
    ch[1]=0; //saturation change
    merge(ch,frame);
}
void imageCallback(const std_msgs::UInt8MultiArray::ConstPtr& array)
{
  try
  {
    Mat frame = imdecode(array->data, 1);
    imshow("view", frame);
    // ROS_INFO("recieve msg time = %lf\n",(double)(clock()-start)/CLOCKS_PER_SEC);
    /*
    //frame의 속성을 변환
    change_hval(frame);
    imshow("what",frame);
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
  cv::namedWindow("view");
  cv::startWindowThread();
  start=clock();
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("mat_msg", 100, imageCallback);
  ros::spin();
  destroyWindow("view");
}