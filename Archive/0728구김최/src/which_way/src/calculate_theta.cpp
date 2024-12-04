#include<ros/ros.h>
#include<opencv2/opencv.hpp>
#include<cv_bridge/cv_bridge.h>
#include<iostream>
#include<std_msgs/UInt8MultiArray.h>
#include<algorithm>
#include<math.h>
#include"which_way/theta.h"
using namespace cv;
using namespace std;
void dbg(){
	ROS_INFO("AAA");
}
ros::Publisher calculate_theta;
int val = 25;
int col = 119;
void DLX(Mat& line, int &v, int &id)
{
	int cnt = 0;
	for(int i = 0; i < val; i++)//DLX
	{
		cnt += !(!(line.at<uchar>(col, i)));
	}
	int max = cnt;
	int dlx = 0;
	for(int i = 1; i < 320 - val; i++)
	{
		cnt += !(!(line.at<uchar>(col, i + val - 1)));
		cnt -= !(!(line.at<uchar>(col, i - 1)));
		if(cnt > max) max = cnt, dlx = i;
	}
	v = max; id = dlx;
}
void DRX(Mat& line, int &v, int &id)
{
	int cnt = 0;
	for(int i = 320; i < 320 + val; i++)//DRX
	{
		cnt += !(!(line.at<uchar>(col, i)));
	}
	int max = cnt;
	int drx = 0;
	for(int i = 321; i < 640 - val; i++)
	{
		cnt += !(!(line.at<uchar>(col, i + val - 1)));
		cnt -= !(!(line.at<uchar>(col, i - 1)));
		if(cnt > max) max = cnt, drx = i;
	}
	v = max; id = drx;
}
void ULX(Mat& line, int &v, int &id)
{
	int cnt = 0;
	for(int i = 0; i < val; i++)//ULX
	{
		cnt += !(!(line.at<uchar>(0, i)));
	}
	int max = cnt;
	int ulx = 0;
	for(int i = 1; i < 320 - val; i++)
	{
		cnt += !(!(line.at<uchar>(0, i + val - 1)));
		cnt -= !(!(line.at<uchar>(0, i - 1)));
		if(cnt > max) max = cnt, ulx = i;
	}		
	v = max; id = ulx;
}
void URX(Mat& line, int &v, int &id)
{
	int cnt = 0;
	for(int i = 320; i < 320 + val; i++)//URX
	{
		cnt += !(!(line.at<uchar>(0, i)));
	}
	int max = cnt;
	int urx = 0;
	for(int i = 321; i < 640 - val; i++)
	{
		cnt += !(!(line.at<uchar>(0, i + val - 1)));
		cnt -= !(!(line.at<uchar>(0, i - 1)));
		if(cnt > max) max = cnt, urx = i;
	}
	v = max; id = urx;
}
void imageCallback(const std_msgs::UInt8MultiArray::ConstPtr& array)
{
try
{
	which_way::theta msg;
	Mat frame = imdecode(array->data, 1);
	Mat mat_line(frame, Rect(Point(0, 360), Point(640, 480)));
	Mat mat_line_gray,tmp;
	Mat line;
	cvtColor(mat_line, tmp, COLOR_HSV2BGR);
	cvtColor(tmp, mat_line_gray, COLOR_BGR2GRAY);
	threshold(mat_line_gray, line, 100, 255, THRESH_BINARY);
	imshow("oh",line);
	//-------------------------------------------------------------------
	int cnt, max;
	int dlx, drx, ulx, urx;
	int dlx_v, drx_v, ulx_v, urx_v;
	int cnt_of_left = 0;
	int cnt_of_right = 0;
	DLX(line, dlx_v, dlx);	
	DRX(line, drx_v, drx);
	double th;
	if(dlx_v < cnt_of_left) // 왼쪽 차선이 보이지 않는 경우 - 오른쪽 차선으로만 판단
	{
		DRX(line, drx_v, drx);
		URX(line, urx_v, urx);
		th = atan((drx - urx) / col);
		if(th >= 0) // 좌회전 경우
		{
			msg.data = -th;
		}
		else // 우회전 경우
		{
			msg.data = -th;
		}
	}
	else if(drx_v < cnt_of_right) // 오른쪽 차선이 보이지 않는 경우 - 왼쪽 차선으로만 판단
	{
		DLX(line, dlx_v, dlx);
		ULX(line, ulx_v, ulx);
		th = atan((ulx - dlx) / col);
		if(th >= 0) // 우회전 경우
		{
			msg.data = th;
		}
		else // 좌회전 경우
		{
			msg.data = th;
		}
	}
	else
	{
		DRX(line, drx_v, drx);
		ULX(line, ulx_v, ulx);
		URX(line, urx_v, urx);	
		//----------------------------------------------------------------------
		dlx += val/2;
		drx += val/2;
		ulx += val/2;
		urx += val/2;
		//-----------------------------------------------------------------------
		double ans_fx=((dlx-ulx)*ulx-(drx-urx)*urx)/(dlx-ulx-drx+urx);
		double ans_fy=((dlx-ulx)/col)*(ans_fx-ulx);
		double mid_x=(dlx+drx)/2;
		double mid_y=col;
		//------------------------------------------------------------------------
		th = atan((ans_fx-mid_x)/(ans_fy-mid_y));
		msg.data = th;
		ROS_INFO("%lf && %lf %lf %lf %lf\n",th, ans_fx, ans_fy, mid_x, mid_y);	
	}
	//메세지에 이 값 저장해서 보내기
	calculate_theta.publish(msg);	
	waitKey(10);
	//메세지에 이 값 저장해서 보내기
	waitKey(10);
	}
	catch (cv_bridge::Exception& e)
	{
	ROS_ERROR("cannot decode image");
	}
}
int main(int argc, char **argv)
{
ros::init(argc, argv, "calculate_theta");
//cv::namedWindow("view");
//cv::startWindowThread();
ros::NodeHandle nh;
calculate_theta = nh.advertise<which_way::theta>("theta", 100);
//ros::Subscriber sub = nh.subscribe("mat_msg", 100, f);
ros::Subscriber sub = nh.subscribe("mat_msg", 100, imageCallback);
 ros::spin();
// destroyWindow("view");
}