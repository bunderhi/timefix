#include "ros/ros.h"
#include <pluginlib/class_list_macros.h>
#include "nodelet/nodelet.h"
#include "std_msgs/String.h"

namespace nodelet_timefix
{

  class Timefix : public nodelet::Nodelet
  {
  
  
  void onInit(){
    ros::NodeHandle& private_nh = getPrivateNodeHandle();

    sub = private_nh.subscribe("incoming", 10, &Timefix::messageCb, this);
    pub = private_nh.advertise<std_msgs::String>("outgoing", 10);
    ROS_INFO("TimeFix Initialized");
  };

  // must use a ConstPtr callback to use zero-copy transport
  void messageCb(const std_msgs::StringConstPtr message){

    // can republish the old message no problem, since we're not modifying it
    pub.publish(message);

    std_msgs::String new_message;
    new_message.data = message->data + " fizz buzz";
    pub.publish(new_message);

  }

  ros::Subscriber sub;
  ros::Publisher pub;
  };

PLUGINLIB_EXPORT_CLASS(nodelet_timefix::Timefix, nodelet::Nodelet);

} // namespace nodelet_timefix
