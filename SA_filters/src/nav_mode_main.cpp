// this guy gets the data; doesn' tpublish

#include "SA_filters/nav_mode.h"

using namespace nav_mode;

ImageConverter* image_converter_ptr_ = nullptr;  // global variable

void GrabImageCB(const sensor_msgs::ImageConstPtr& msg) {
  image_converter_ptr_->updateImage(*msg);
}

void GrabTwistCB(const geometry_msgs::Twist::ConstPtr& msg) {
  image_converter_ptr_->updateTwist(*msg);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "image_converter_node");

  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  image_converter_ptr_ =
      new ImageConverter(nh);  // this allows us to do something with the nh

  image_transport::Subscriber img_sub =
      it.subscribe("/fisheye_camera/fisheye_image_raw", 1, GrabImageCB);

  ros::Subscriber twist_sub =
      nh.subscribe("/husky_velocity_controller/cmd_vel", 1, GrabTwistCB);

  ros::Rate r(10);

  while (ros::ok()) {
    ros::spinOnce();
    image_converter_ptr_->run();
    r.sleep();
  }
  delete image_converter_ptr_;
}
