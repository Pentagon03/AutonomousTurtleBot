/*
This Code is for CrossWalk
*/
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <unistd.h>
#include <termios.h>
#include <map>
#include <std_msgs/UInt8MultiArray.h>
using namespace cv;
using namespace std;
void dbg(){
  ROS_INFO("STILL WORKING!!");
}
ros::Publisher pub;
std::map<char, std::vector<float>> moveBindings{
    {'#', {0,0}},
    {'T', {1,0.15}},
    {'i', {1, 0}},
    {'o', {1, -1}},
    {'j', {0, 1}},
    {'l', {0, -1}},
    {'u', {1, 1}},
    {',', {-1, 0}},
    {'.', {-1, 1}},
    {'m', {-1, -1}},
    {'I', {1.5, 0}},
    {'O', {1, -1.5}},
    {'J', {0, 0}},
    {'L', {0, 0}},
    {'U', {1, 1.5}},
    {'<', {-1, 0}},
    {'>', {-1, 0}},
    {'M', {-1, 0}},
};
// Map for speed keys
//방향성이 정해진 상태에서 속도를 증가/감소시킨다. (비율)
std::map<char, std::vector<float>> speedBindings
{
  {'q', {1.1, 1.1}},
  {'z', {0.9, 0.9}},
  {'w', {1.1, 1}},
  {'x', {0.9, 1}},
  {'e', {1, 1.1}},
  {'c', {1, 0.9}}
};
// Reminder message
const char* msg = R"(
Reading from the keyboard and Publishing to Twist!
---------------------------
Moving around:
   u    i    o
   j    k    l
   m    ,    .
  U,L : Faster Rotation
anything else : stop
q/z : increase/decrease max speeds by 10%
w/x : increase/decrease only linear speed by 10%
e/c : increase/decrease only angular speed by 10%
CTRL-C to quit
)";
// Init variables
/*
완벽한 속도
float speed(0.05); // Linear velocity (m/s)
float turn(0.3); // Angular velocity (rad/s)
*/
// 0.08 정도는 되어야 빠른 속도이다.
float speed(0.11); // Linear velocity (m/s)
float turn(0.42); // Angular velocity (rad/s)
float x(0), y(0), z(0), th(0); // Forward/backward/neutral direction vars
char key(' ');
// Create Twist message
geometry_msgs::Twist twist;
bool MasterFlag=false;
//헤더파일------------------------------
Mat frame; //영상받을 변수
Mat mat_line_gray,tmp,Line;
double theta;
int val = 25;
int row = 49;
int lmid=300,rmid=320; 
char Key;
int flag;
int flag_left,flag_right;
//전역변수 -------------------------------
//함수들 --------------------------------
//calculate_theta theta값 찾기---------
void DLX(Mat& Line, int &v, int &id);
void DRX(Mat& Line, int &v, int &id);
void ULX(Mat& Line, int &v, int &id);
void URX(Mat& Line, int &v, int &id);
void stopAll(){
    twist.linear.x = 0;
    twist.linear.y = 0;
    twist.linear.z = 0;
    twist.angular.x = 0;
    twist.angular.y = 0;
    twist.angular.z = 0;
    // Publish it and resolve any remaining callbacks
    pub.publish(twist);
}
int crosswalk();
void find_theta();
int traffic_light();
void Determinant();
void Move();
void imageCallback(const std_msgs::UInt8MultiArray::ConstPtr& array);
//------------------------------------------
int main(int argc, char **argv)
{
  ros::init(argc, argv, "total_code");
  cv::namedWindow("view");
  cv::startWindowThread();
  ros::NodeHandle nh;
  puts("ASDFASD");
  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  ros::Subscriber sub = nh.subscribe("mat_msg", 10, imageCallback);
  ros::spin();
  destroyWindow("view");
}
//------------------------------------------
int crosswalk()
{
    int cnt=0;
    //Use Mat Line
    int r=Line.rows/2;
    for(int i=0;i<Line.cols;i++)
        if(bool(Line.at<uchar>(r, i)))
            ++cnt;
    if(cnt > Line.cols/2)
	{	
		Key='#';//멈추는 키 
		Move();
		waitKey(1000*5);//5초 멈춤
		Key='T';
		Move();
		waitKey(1000*3.9);//3초간 직진 
    return 1;
	}
    return 0;
}


int traffic_light()
{
  // ROS_INFO("%d %d",frame.rows,frame.rows);
  Mat mat_traffic(frame, Rect(Point(560, 0), Point(640, 120)));
  imshow("mat_traffic", mat_traffic);
  int cnt_red=0, cnt_orange=0, cnt_green=0;
  for(int i = 0; i < mat_traffic.rows; i++)
  {
    for(int j = 0; j < mat_traffic.rows; j++)
    {
      uchar p = mat_traffic.at<Vec3b>(i,j)[0];
      uchar v = mat_traffic.at<Vec3b>(i,j)[1];
      if((p <= 10 || p >= 170) && v > 150) cnt_red++;
      if(p >= 50 && p <= 70 && v > 150) cnt_green++;
      if(p >= 20 && p <= 40 && v > 150) cnt_orange++;
    }
  }
  if(cnt_red > cnt_green && cnt_red > cnt_orange)
  {
    return 1;
  }
  else return 0;
}
void imageCallback(const std_msgs::UInt8MultiArray::ConstPtr& array)
{
  try
  {
    frame = imdecode(array->data, 1);
    imshow("view", frame);
    if(frame.empty()){
      printf("ERROR!\n"); return;
    }
    if(waitKey(1)=='s'){
      stopAll();
      MasterFlag=true;
      puts("STOP!!");
      return;
    }
    else if(waitKey(1)=='g'){
      puts("GO AGAIN!");
      MasterFlag=false;
    }
    if(MasterFlag==true) {
      return;
    }
    // if(traffic_light()==1)
    // {
    //     return;
    // }
    ROS_INFO("%lf",theta);
    find_theta();
    Determinant();
    Move();
    crosswalk();
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cannot decode image");
  }
  waitKey(1);
}
void find_theta()
{
  try{  
  Mat mat_line(frame, Rect(Point(0, 425), Point(610, 475)));
  cvtColor(mat_line, tmp, COLOR_HSV2BGR);
  cvtColor(tmp, mat_line_gray, COLOR_BGR2GRAY);
  threshold(mat_line_gray, Line, 150, 255, THRESH_TOZERO);
  imshow("oh",Line);
  int cnt, max;
  int dlx, drx, ulx, urx;
  int dlx_v, drx_v, ulx_v, urx_v;
  int cnt_of_left = 5;
  int cnt_of_right = 5;
  DLX(Line, dlx_v, dlx);
  DRX(Line, drx_v, drx);
  double th;
      /*
    try catch 구문 한 다음 exception에 stopAll 함수 호출하기
    */
    if(dlx_v < cnt_of_left &&drx_v < cnt_of_right){
      puts("no line");
      theta=0; 
      flag_left=flag_right=0;
    }
    if(dlx_v < cnt_of_left) // 왼쪽 차선이 보이지 않는 경우 - 오른쪽 차선으로만 판단
    {
        puts("no left");
        flag_left=1;
        flag_right=0;
        theta=0;
        // // DRX(Line, drx_v, drx);
        // URX(Line, urx_v, urx);
        // th = atan((drx - urx) / row);
        // theta = -th;
    }
    else if(drx_v < cnt_of_right) // 오른쪽 차선이 보이지 않는 경우 - 왼쪽 차선으로만 판단
    { 
        puts("no right");
        theta=0;
        flag_left=0;
        flag_right=1;
        // // DLX(Line, dlx_v, dlx);
        // ULX(Line, ulx_v, ulx);
        // th = atan((ulx - dlx) / row);
        // theta = th;
    }
    else
    {
        puts("all");
        flag_left=flag_right=0;
        // DRX(Line, drx_v, drx);
        ULX(Line, ulx_v, ulx);
        URX(Line, urx_v, urx);
        dlx += val/2;
        drx += val/2;
        ulx += val/2;
        urx += val/2;
        double ans_fx=(double(dlx-ulx)*ulx-(drx-urx)*urx)/(dlx-ulx-drx+urx);
        double ans_fy=(double(dlx-ulx)/row)*(ans_fx-ulx);
        double mid_x=(dlx+drx)/2.0;
        double mid_y=row;
        printf("%lf %lf %lf %lf :: ",ans_fx,ans_fy,mid_x,mid_y);
        th = atan((ans_fx-mid_x)/(ans_fy-mid_y));
        theta = th;
        theta*=57.3; //각도를 세타로 바꿔준다.
        theta*=-1;
        ROS_INFO("%f",theta);
    }
    waitKey(1);
  }
  catch(int EE){
        ROS_INFO("DOUBLE VALUE IS WRONG");
        stopAll();
  }
}
void Determinant()
{
  printf("%d %d %lf\n",flag_left,flag_right,theta);
  if(flag_left)
  {
      Key='U';
  }
  else if(flag_right)
  {
      Key='o';
  }
  else
  {
    if(theta>=-10 && theta<=10){
     Key='i';
    }
    else if(theta>40){
      Key='U';
    }
    else if(theta>10){
      Key='u';
    }
    else if(theta<-40){
      key='O';
    }
    else if(theta<-10){
      key='o';
    }
  } 
}
void Move()
{
    printf("%c",Key);
    if (moveBindings.count(Key) == 1)
    {
      // Grab the direction data
      x = moveBindings[Key][0];
      th = moveBindings[Key][1];
      // printf("\rspeed %f\tturn %f|%c", speed, turn, key);
    }
    else if (speedBindings.count(Key) == 1)
    {
      // Grab the speed data
      speed = speed * speedBindings[Key][0];
      turn = turn * speedBindings[Key][1];
    }
    else
    {
      x = 0;
      th = 0;
      if (Key == 'p')
      {
        printf("\n\n                 .     .\n              .  |\\-^-/|  .    \n             /| } O.=.O { |\\\n\n                 CH3EERS\n\n");
        return;
      }
      // printf("\rCurrent: speed %f\tturn %f | Invalid command! %c", speed, turn, key);
    }
    // Update the Twist message
    twist.linear.x = x * speed;
    twist.angular.z = th * turn;
    twist.linear.y = twist.linear.z = 0;
    twist.angular.x = twist.angular.y = 0;
    // Publish it and resolve any remaining callbacks
    pub.publish(twist);
    waitKey(1);
}
void DLX(Mat& Line, int &v, int &id)
{
  puts("WHY");
  int cnt = 0;
  for(int i = 0; i <val; i++){//DLX
    cnt += bool(Line.at<uchar>(row, i));
  }
  int max = cnt;
  int dlx = 0;
  for(int i = 1; i <=200; i++)
  {
    cnt += bool(Line.at<uchar>(row, i+val-1));
    cnt -= bool(Line.at<uchar>(row, i-1));
    if(cnt > max) max = cnt, dlx = i;
    if(cnt>22) break;
  }
  v = max; id = dlx;
  // printf("DLX %d %d\n",max,dlx);
}
void DRX(Mat& Line, int &v, int &id)
{
  int cnt = 0;
  for(int i = 600-200; i <=600-200+val-1; i++){//DRX
    cnt += bool(Line.at<uchar>(row, i));
  }
  int max = cnt;
  int drx = 600-200;
  for(int i = 600-200+1; i <= 600-val ; i++)
  {
    cnt += bool(Line.at<uchar>(row, i+val-1));
    cnt -= bool(Line.at<uchar>(row, i-1));
    if(cnt > max) max = cnt, drx = i;
    if(cnt>22) break;
  }
  v = max; id = drx;
  // printf("DRX %d %d\n",max,drx);
}
void ULX(Mat& Line, int &v, int &id)
{
  int cnt = 0;
  for(int i = 0; i <val; i++){//ULX
    cnt += bool(Line.at<uchar>(0, i));
  }
  int max = cnt;
  int ulx = 0;
  for(int i = 1; i <200; i++)
  {
    cnt += bool(Line.at<uchar>(0, i+val-1));
    cnt -= bool(Line.at<uchar>(0, i-1));
    if(cnt > max) max = cnt, ulx = i;
    if(cnt>22) break;
  }
  v = max; id = ulx;
  // printf("ULX %d %d\n",max,ulx);
}
void URX(Mat& Line, int &v, int &id)
{
  int cnt = 0;
  for(int i = 600-200; i <=600-200+val-1; i++){//URX
    cnt += bool(Line.at<uchar>(0, i));
  }
  int max = cnt;
  int urx = 600-200;
  for(int i = 600-200+1; i <= 600-val ; i++)
  {
    cnt += bool(Line.at<uchar>(0, i+val-1));
    cnt -= bool(Line.at<uchar>(0, i-1));
    if(cnt > max) max = cnt, urx = i;
    if(cnt>22) break;
  }
  v = max; id = urx;
  // printf("URX %d %d\n",max,urx);
}
