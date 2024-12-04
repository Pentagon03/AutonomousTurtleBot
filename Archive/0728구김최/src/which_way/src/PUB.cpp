#
//node : pub_video
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include<which_way/theta.h>
using namespace cv;
using namespace std;
int main(int argc,char**argv){
	ros::init(argc,argv,"pub_video");
	ros::NodeHandle nh;
	ros::Publisher pub_video = nh.advertise<which_way::theta>("Theta",100);
	ros::Rate loop_rate(1); //waitKey 와 똑같은 역할

	which_way::theta msg;
	int cnt=0;
	while(ros::ok()){
		msg.stamp=ros::Time::now();
		msg.data=cnt;
		pub_video.publish(msg);
		loop_rate.sleep();
		// ROS_INFO("recieve msg = %d",msg.data);
		++cnt;
	}
	return 0;
}

