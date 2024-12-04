#include "ros/ros.h"                         
#include "test_package1/test_msg1.h"  

void msgCallback(const test_package1::test_msg1::ConstPtr& msg) {

  ROS_INFO("recieve msg = %d", msg->stamp.sec);   
  ROS_INFO("recieve msg = %d", msg->stamp.nsec);  
  ROS_INFO("recieve msg = %d", msg->data);        
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sub1");            
  ros::NodeHandle nh;                       

  ros::Subscriber sub1 = nh.subscribe("test_msg1", 100, msgCallback);

  ros::spin();

  return 0;
}

