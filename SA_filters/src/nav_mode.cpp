#include "SA_filters/nav_mode.h"
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

static const std::string OPENCV_WINDOW = "Image window";

namespace nav_mode {

ImageConverter::ImageConverter(ros::NodeHandle& nh) : nh_(nh), it_(nh) {
  it_pub_ = it_.advertise("pub_img", 1);
  
    
  ROS_INFO("CONSTRUCTED");
}

void ImageConverter::run() 
{ ROS_INFO("WEEE!"); 

cv_bridge::CvImagePtr cv_ptr;
//cv_ptr = cv_bridge::toCvCopy(this->img_, sensor_msgs::image_encodings::BGR8);



    // Output modified video stream
    it_pub_.publish(cv_ptr->toImageMsg());

    cv::waitKey(3);

  cv::namedWindow(OPENCV_WINDOW);

}

void ImageConverter::updateImage(const sensor_msgs::Image& img) {
  this->img_ = img;
  ROS_INFO("GOT NEW IMAGE");
  ROS_LOG(img)
}

void ImageConverter::updateTwist(const geometry_msgs::Twist& vel) {
  this->vel_ = vel;

  ROS_INFO_STREAM("x velocity: " << vel_.linear.x
                                 << " angular velocity: " << vel_.angular.z);

  ROS_INFO("GOT NEW TWIST");
}

}  // namespace nav_mode
