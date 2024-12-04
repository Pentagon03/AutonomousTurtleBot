#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc,char **argv){
 ros::init(argc,argv,"ex1");

 Mat org(100,100,CV_8UC3, Scalar(255,0,0));
 // imshow("org",org);

 Mat sub1(org,Rect(20,0,20,50));
 Mat sub2(org,Rect(Point(40,0),Point(60,50)));

 //B,G,R
 sub1 = Scalar(0,255,0,100); //green color
 sub2 = Scalar(0,0,255,100); //red color
 
 // imshow("sub1",sub1);
 // imshow("sub2",sub2);
 imshow("new",org);
 
 // waitKey(0);

 vector<Mat> ch;
 split(org,ch); //separate by channel
 char wname[10];
 /*
 for(int i=0;i<org.channels();i++){
 	sprintf(wname,"ch%d",i);
 	imshow(wname,ch[i]);
 }
*/
 Mat merged;
 ch[0]=ch[0]/2;
 ch[1]=ch[0]/2;
 merge(ch,merged);
 imshow("new2",merged);
 puts("I Love You So Much");
 
 waitKey(0);
 return 0;
}
