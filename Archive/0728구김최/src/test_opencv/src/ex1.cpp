//ex 10 , Threshold
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc,char**argv){
	ros::init(argc,argv,"ex1");
	Mat org = imread("/home/kusin/imgs/apple.jpg",IMREAD_UNCHANGED);
	imshow("original",org);
	waitKey(0);
	return 0;
}
/*
//ex 9
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc,char**argv){
	ros::init(argc,argv,"ex1");
	Mat org = imread("/home/kusin/imgs/EinStein.tif",IMREAD_GRAYSCALE);
	Mat chg;

	equalizeHist(org,chg); //histogram equalization

	imshow("original",org);
	imshow("negative",chg);

	waitKey(0);
	return 0;
}
*/
/*
//ex 7-2
#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc,char**argv){
	ros::init(argc,argv,"ex1");
	Mat img = imread("/home/kusin/imgs/lena.png",IMREAD_COLOR);
	//IMREAD_COLOR, IMREAD_GRAYSCALE 등
	Mat hsv;
	cvtColor(img,hsv,COLOR_BGR2HSV);
	imshow("img",img);
	imshow("hsv",hsv);
	int red_cnt=0,green_cnt=0;
	for(int i=0;i<hsv.rows;i++){
		for(int j=0;j<hsv.cols;j++){
			uchar p = hsv.at<Vec3b>(i,j)[0];
			if(p<=10 || p>=170)
				red_cnt++;
			else if(p>=50 && p<=70)
				green_cnt++;
		}
	}
	printf("red_pixel = %d \n green_pixel = %d\n",red_cnt,green_cnt);
	waitKey(0);
	return 0;
}
*/





/*
//ex 7-1
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc,char**argv){
	ros::init(argc,argv,"ex1");
	Mat img = imread("/home/kusin/imgs/lena.png",IMREAD_COLOR);
	Mat gray;
	cvtColor(img,gray,COLOR_BGR2GRAY);
	imshow("img",img);
	int dark_cnt=0;
	for(int i=0;i<gray.rows;i++){
		uchar *row_ptr = gray.ptr<uchar>(i);
		for(int j=0;j<gray.cols;j++){
			dark_cnt+=(row_ptr[j]<50)?1:0; //count which pixel val < 50
		}
	}
	printf("dark_pixel=%d\n",dark_cnt);
	waitKey(0);
	return 0;
}
*/
/*
//ex6
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

// //ex5
// #include <ros/ros.h>
// #include <opencv2/opencv.hpp>
// #include <cv_bridge/cv_bridge.h>
// #include <iostream>

// using namespace cv;
// using namespace std;

// int main(int argc,char**argv){
// 	ros::init(argc,argv,"ex1");

// 	Mat img = imread("/home/kusin/imgs/apple.jpg",IMREAD_COLOR);
// 	imshow("orginal",img);

// 	Mat hsv;
// 	cvtColor(img,hsv,COLOR_BGR2HSV);
// 	imshow("hsv",hsv);

// 	vector<Mat> ch;
//  	split(hsv,ch); //separate by channel
//  	char wname[10];
//  	for(int i=0;i<hsv.channels();i++){
//  		sprintf(wname,"ch%d",i);
//  		imshow(wname,ch[i]);
//  	}

//  	Mat merged;
//  	ch[2]/=2;
//  	merge(ch,merged);

//  	cvtColor(merged,hsv,COLOR_HSV2BGR);
//  	imshow("merged",hsv);
//  	waitKey(0);
//  	/*
// 	Mat gray;
// 	cvtColor(img,gray,COLOR_BGR2GRAY); //change to grayscale
// 	imshow("gray",gray);

// 	imwrite("imgs/lena_gray.png",gray);
// 	waitKey(0);
// 	return 0;
// 	*/
// }

//ex1 
/*
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc,char **argv){
 ros::init(argc,argv,"ex1");

 Mat M1;
 Mat M2(20,150,CV_8UC3);
 Mat M3(20,150,CV_8UC3,Scalar(255,0,0));
 Mat M4(Size(20,150),CV_8UC3,Scalar(0,0,255));

 printf("img size=[%d]*[%d] flag=[%x]\n",M2.cols,M2.rows,M2.flags);
 imshow("M2",M2);
 printf("img size=[%d]*[%d] flag=[%x]\n",M3.cols,M3.rows,M3.flags);
 imshow("M3",M3);
 printf("img size=[%d]*[%d] flag=[%x]\n",M4.cols,M4.rows,M4.flags);
 imshow("M4",M4);

 waitKey(0);

 return 0;
}
*/
