//node : pub_video
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include <std_msgs/UInt8MultiArray.h>
using namespace cv;
using namespace std;
int main(int argc,char**argv){
	ros::init(argc,argv,"pub_video");
	ros::NodeHandle nh;
	ros::Publisher pub_video = nh.advertise<std_msgs::UInt8MultiArray>("mat_msg",100);
	// ros::Rate loop_rate(1); //36번 라인과 연결됨
	Mat frame,chg;
	VideoCapture cap(0);
	while(ros::ok())
	{
		cap>>frame;
		cvtColor(frame,chg,COLOR_BGR2HSV);
		std::vector<uchar> encode;
		std::vector<int> encode_param;
		encode_param.push_back(CV_IMWRITE_JPEG_QUALITY);
		encode_param.push_back(20);
		cv::imencode(".jpg", chg, encode, encode_param);
        cv::Mat decode = cv::imdecode(encode, 1);
        cv::imshow("decode", decode);
		//imshow("video",chg);
		std_msgs::UInt8MultiArray msgArray;
        msgArray.data.clear();
        msgArray.data.resize(encode.size());
        std::copy(encode.begin(), encode.end(), msgArray.data.begin());
		pub_video.publish(msgArray);
		if(waitKey(10)=='q') break;
		// loop_rate.sleep();
	}
	return 0;
}
/*
//Video
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc,char**argv){
	ros::init(argc,argv,"ex1");

	Mat frame;
	VideoCapture cap("/home/kusin/imgs/test4.mkv");
	while(1){
		cap>>frame;
		imshow("video",frame);
		if(waitKey(10)=='s')
			break;
	}
}
*/

