#include "ros/ros.h"
#include <pluginlib/class_list_macros.h>
#include "nodelet/nodelet.h"
#include "sensor_msgs/Imu.h"

namespace nodelet_timefix
{

  class Timefix : public nodelet::Nodelet
  {
  
  
  void onInit(){
    ros::NodeHandle& private_nh = getPrivateNodeHandle();

    sub = private_nh.subscribe("incoming", 10, &Timefix::messageCb, this);
    pub = private_nh.advertise<sensor_msgs::Imu>("outgoing", 10);
    ROS_INFO("TimeFix Initialized");
  };

  // must use a ConstPtr callback to use zero-copy transport
  void messageCb(const sensor_msgs::Imu::ConstPtr& message){

    // can republish the old message no problem, since we're not modifying it
    pub.publish(message);

    sensor_msgs::Imu new_message;
    new_message.header = message->header;
    new_message.angular_velocity = message->angular_velocity;
    new_message.angular_velocity_covariance = message->angular_velocity_covariance;
    new_message.linear_acceleration = message->linear_acceleration;
    new_message.linear_acceleration_covariance = message->linear_acceleration_covariance;
    new_message.orientation = message->orientation;
    new_message.orientation_covariance = message->orientation_covariance;
    pub.publish(new_message);

  }

  ros::Subscriber sub;
  ros::Publisher pub;
  };

PLUGINLIB_EXPORT_CLASS(nodelet_timefix::Timefix, nodelet::Nodelet);

} // namespace nodelet_timefix
