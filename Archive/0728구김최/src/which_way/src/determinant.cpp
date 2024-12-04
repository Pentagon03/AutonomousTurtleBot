//node : determinant
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <which_way/theta.h>
#include <traffic_light/Res_Color.h>
#include <which_way/Res_Key.h>
using namespace cv;
using namespace std;
void dbg(){
  ROS_INFO("AAA");
}
int flag=0;
int l,a;
ros::Publisher pub_1;
which_way::Res_Key Res_Key;
time_t cur_time=0;
void msgCallback1(const which_way::theta::ConstPtr& msg)
{
  if(msg==NULL||flag==1) return;
  if((clock()-cur_time)*CLOCKS_PER_SEC > 1){
    ROS_INFO("%f",msg->data);
    cur_time=clock();
  }
    if(msg->data>-10 && msg->data<=10)
    {
      if(l<10)
      {
        l++;
        Res_Key.key='i';
        dbg();
        pub_1.publish(Res_Key);
      }
      else if(a>0)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
      }
      else if(a<0)
      {
        a++;
        Res_Key.key='t';
        pub_1.publish(Res_Key);
      }
  }
    else if(msg->data>10&&msg->data<=30)
    {
      if(l<9)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>9)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
    if(a>1)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<1)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>30&&msg->data<=50)
    {
      if(l<7)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>7)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>3)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<3)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>50&&msg->data<=70)
    {
      if(l<6)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>6)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>4)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<4)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>70&&msg->data<=90)
  {
    if(l<4)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>4)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>6)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<6)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>-30&&msg->data<=-10)
  {
    if(l<9)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>9)
      {
        l++;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>-1)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<-1)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>-50&&msg->data<=-30)
  {
    if(l<7)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>7)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>-3)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<-3)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>-70&&msg->data<=50)
  {
    if(l<6)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>6)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>-4)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<-4)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  
  else if(msg->data>=-90&&msg->data<=70)
  {
    if(l<4)
      {
        l++;
      Res_Key.key='i';
        pub_1.publish(Res_Key);
    }
    else if(l>4)
      {
        l--;
      Res_Key.key='l';
        pub_1.publish(Res_Key);
    }
      if(a>-6)
      {
        a--;
        Res_Key.key='b';
        pub_1.publish(Res_Key);
    }
    else if(a<-6)
    {
      a++;
      Res_Key.key='t';
      pub_1.publish(Res_Key);
    }
  }
  waitKey(100);
}

void msgCallback2(const traffic_light::Res_Color::ConstPtr& msg)
{
  if(!msg) return;
  if(msg->color=='R'&&msg->data>=100) //신호등 픽셀 개수
  {
    Res_Key.key='k';
    flag=1;
    pub_1.publish(Res_Key);
  }
  else if(msg->color=='G'&&msg->data>=100)
  {
    if(flag==1)
    {
      Res_Key.key='i';
      flag=0;
      pub_1.publish(Res_Key);
    }
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "determinant");
//  cv::namedWindow("view");
//  cv::startWindowThread();
  ros::NodeHandle nh;
  pub_1 = nh.advertise<which_way::Res_Key>("Res_Key", 100);
  waitKey(100000);
  ros::Subscriber sub1 = nh.subscribe("theta", 100, msgCallback1);
  // ros::Subscriber sub2 = nh.subscribe("Res_Color", 100, msgCallback2);
  ros::spin();
}