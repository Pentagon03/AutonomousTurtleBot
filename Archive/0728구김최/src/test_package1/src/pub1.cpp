#include "ros/ros.h"                    
#include "test_package1/test_msg1.h"    

int main(int argc, char **argv) {
  ros::init(argc, argv, "pub1");     
  ros::NodeHandle nh;                           
  ros::Publisher pub1 = nh.advertise<test_package1::test_msg1>("test_msg1", 100);
  ros::Rate loop_rate(1);

  test_package1::test_msg1 msg;     
  int count = 0;                    

  while (ros::ok()) {
    msg.stamp = ros::Time::now();           
    msg.data  = count;                      

    ROS_INFO("send msg = %d", msg.stamp.sec);   
    ROS_INFO("send msg = %d", msg.stamp.nsec);  
    ROS_INFO("send msg = %d", msg.data);       

    pub1.publish(msg);          
    loop_rate.sleep();                      
    ++count;                                
  }
  return 0;
}

