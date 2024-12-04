//node : lane_trace
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include <std_msgs/UInt8MultiArray.h>
#include<which_way/theta.h>
//message type : theta.msg
//message 구성 (추후 변경)
/*
time stamp
int32 data // 무조건 int32로 해야 동작함
*/
using namespace cv;
using namespace std;
void print(const which_way::theta::ConstPtr&msg){
	ROS_INFO("recieve msg = %d",msg->stamp.sec);
	ROS_INFO("recieve msg = %d",msg->stamp.nsec);
	ROS_INFO("recieve msg = %d",msg->data);
}
void msgCallback(const which_way::theta::ConstPtr& msg)
{
	print(msg);
}
int main(int argc,char**argv){
	ros::init(argc,argv,"lane_trace");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("Theta", 100, msgCallback);
	ros::spin();
	return 0;
}

