#pragma once

#include <sensor_msgs/Image.h>
#include "geometry_msgs/Twist.h"
#include "image_transport/image_transport.h"
#include "ros/ros.h"

namespace nav_mode {

class ImageConverter {
 public:
  ImageConverter(ros::NodeHandle& nh);  // constructor name

  void run();

  void updateImage(const sensor_msgs::Image& img);

  void updateTwist(const geometry_msgs::Twist& vel);

 private:
  ros::NodeHandle nh_;

  image_transport::ImageTransport it_;  // access "_" like "self"

  image_transport::Publisher it_pub_;

  sensor_msgs::Image img_;

  geometry_msgs::Twist vel_;
};

}  // namespace nav_mode
