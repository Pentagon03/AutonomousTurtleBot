#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc,char**argv){
	ros::init(argc,argv,"std1");
	Mat M1(20,50,CV_8UC3,Scalar(255,255,255));
	Mat sub1(M1,Rect(Point(0,0),Point(10,10)));
	imshow("org",M1);
	vector<Mat> ch;
	split(M1,ch);
	char wname[10];
	for(int i=0;i<M1.channels();i++){
		sprintf(wname,"ch%d",i);
		imshow(wname,ch[i]);
	}
	// ch[0]=ch[0]/2; //B
	// ch[1]=ch[1]/2;
	ch[1]=Scalar(0,0,0);
	Mat merged;
	merge(ch,merged);
	imshow("merged",merged);
	// sub1 = Scalar(0,0,0);
	// imshow("teawt",M1);
	// imshow("change",sub1);
	waitKey(0);
	return 0;
}