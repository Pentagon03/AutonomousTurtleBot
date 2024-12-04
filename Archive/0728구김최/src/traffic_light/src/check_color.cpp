#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include<std_msgs/UInt8MultiArray.h>
#include<algorithm>
#include"traffic_light/Res_Color.h"
using namespace cv;
using namespace std;
ros::Publisher check_color;
void imageCallback(const std_msgs::UInt8MultiArray::ConstPtr& array)
{
	traffic_light::Res_Color msg;
try
{
	Mat frame = imdecode(array->data, 1);
	//printf("colume = %d, row = %d\n",frame.cols, frame.rows);
	Mat mat_traffic(frame, Rect(Point(560, 0), Point(640, 120)));
	imshow("mat_traffic", mat_traffic);
	//imshow("frame", frame);
    	int cnt_red, cnt_orange, cnt_green;
	for(int i = 0; i < mat_traffic.cols; i++)
	{
		for(int j = 0; j < mat_traffic.rows; j++)
		{
			uchar p = mat_traffic.at<Vec3b>(i,j)[0];
			if(p <= 10 || p >= 170) cnt_red++;
			if(p >= 50 && p <= 70) cnt_green++;
			if(p >= 20 && p <= 40) cnt_orange++;
		}
	}    
	
	int n1 = max(cnt_red, cnt_orange);
	int max_ = max(n1, cnt_green);
	msg.data = max_; 
	char c;
	if(max_ == cnt_red) c='R';
	else if(max_ == cnt_green) c='G';
	else if(max_ == cnt_orange) c='O';
	msg.color=c;
	check_color.publish(msg);
	waitKey(10);
}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cannot decode image");
	}
}

int main(int argc, char **argv)
	{
	ros::init(argc, argv, "check_color");
	// cv::namedWindow("view");
	// cv::startWindowThread();
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("mat_msg", 100, imageCallback);
	check_color = nh.advertise<traffic_light::Res_Color>("Res_Color", 100);
	ros::spin();
	destroyWindow("view");
	}
