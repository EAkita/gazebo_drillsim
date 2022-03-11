#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/Twist.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;  // to avoid std::string

// Drawing Shapes and lines

static const std::string OPENCV_WINDOW = "Image window";

// declare colors: RGB from husky_cam
cv::Scalar colorBlue = cv::Scalar(0, 0, 255);
cv::Scalar colorRed = cv::Scalar(255, 0, 0);
cv::Scalar colorGreen = cv::Scalar(0, 255, 0);
cv::Scalar colorYellow = cv::Scalar(255, 255, 0);

// Change colors below
cv::Scalar colorOrange = cv::Scalar(10, 70, 255);
cv::Scalar colorWhite = cv::Scalar(255, 255, 255);
int line_thickness = 3;

// rostopic info /husky_velocity_controller/cmd_vel
// pkg name: geometry_msg
// kind of msg that goes on ths topic(name of type itself): Twist

// Now rosmsg show geometry_msgs/Twist -- tells you how to get to the msg

class ImageConverter {
  // list these at the bottom of the class as private
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

  // ros::NodeHandle nh_;
  // ros::Subscriber sub = nh_.subscribe("/husky_velocity_controller/cmd_vel",
  // 1, Callback); settings["text"] = {insitu::STRING, "Hello World!"};
  // double x;

  double x;

 public:
  static void Callback(const geometry_msgs::Twist::ConstPtr &msg)

  {
    // double x = msg->
    double x = msg->linear.x;
    double y = msg->angular.x;
    // ROS_INFO("I heard: [%s]", msg->data.c_str());
    ROS_INFO("lin: %f, ang: %f", x, y);
    // printf("x", x);
    // this->x =  msg->linear.x;
    // this->  x = msg.linear.x;
  }

  ros::Subscriber sub =
      nh_.subscribe("/husky_velocity_controller/cmd_vel", 1, Callback);

 public:
  ImageConverter() : it_(nh_) {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/fisheye_camera_2/fisheye_rear_image_raw",
                               1,
                               &ImageConverter::imageCb,
                               this);
    //   ros::Subscriber sub =
    //   nh_.subscribe("/husky_velocity_controller/cmd_vel", 1,
    //                               &ImageConverter::Callback, this);

    image_pub_ = it_.advertise("/image_converter/output_video", 1);
    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter() { cv::destroyWindow(OPENCV_WINDOW); }

  void imageCb(const sensor_msgs::ImageConstPtr &msg) {
    cv_bridge::CvImagePtr cv_ptr;

    try

    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    // Draw an example circle on the video stream
    if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
      cv::circle(cv_ptr->image,
                 cv::Point(50 + (500 * this->x), 50 + (500 * this->x)),
                 10,
                 CV_RGB(255, 0, 0));

    // Mat cv_ptr->image;

    int nav_line_scale = 500;
    // cout << x;
    arrowedLine(cv_ptr->image,
                Point(718, 972),
                Point(718, 972 + int(nav_line_scale * x)),
                CV_RGB(255, 0, 0),
                line_thickness);
    line(cv_ptr->image,
         Point(50, 50),
         Point(100, 100),
         colorRed,
         line_thickness);
    line(cv_ptr->image,
         Point(50, 50),
         Point(100, 100),
         colorRed,
         line_thickness);

    //  line(img,Point(893, 1185), Point(859,1086), colorRed, line_thickness);
    //  line(img,Point(593, 1089), Point(619, 1089), colorRed, line_thickness);
    //  line(img,Point(831, 1089), Point(862, 1089), colorRed, line_thickness);

    //  line(img,Point(591, 1086), Point(617, 1015), colorYellow,
    //  line_thickness); line(img,Point(859,1086), Point(838,1015), colorYellow,
    //  line_thickness); line(img,Point(618, 1017), Point(646, 1017),
    //  colorYellow, line_thickness); line(img,Point (839, 1017), Point (807,
    //  1017), colorYellow, line_thickness);

    //  line(img,Point (617, 1015), Point (663,874), colorGreen,
    //  line_thickness); line(img,Point(838,1015), Point (790,874), colorGreen,
    //  line_thickness); line(img,Point(638, 955), Point (666,955), colorGreen,
    //  line_thickness); line(img,Point (655, 913), Point (673,913), colorGreen,
    //  line_thickness); line(img,Point (801, 913), Point (781,913), colorGreen,
    //  line_thickness);
    // Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
    //    //Mat img(512, 512, CV_8UC3, blue);

    //    //circle(img,Point(256,256), 155, Scalar(0,70,255),thickness = 10 OR
    //    FILLED); circle(img, Point(256, 256), 155, colorOrange, FILLED);

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    // cv::imshow(OPENCV_WINDOW, img);
    cv::waitKey(3);
    // Output modified video stream
    image_pub_.publish(cv_ptr->toImageMsg());
    // image_pub_.publish(img);
  }
};

int main(int argc, char **argv) {
  // cout << Callback (msg);
  ros::init(argc, argv, "image_converter");

  ImageConverter ic;
  ros::spin();
  return 0;
}

// int main()
// {
//    //declare color blue; type variable = value;
//    //class::type var_name = namespace::type( , , )
//    // same as Scalar(255,0,0) when call function below
//    cv::Scalar colorBlue = cv::Scalar(255, 0, 0);
//    cv::Scalar colorOrange = cv::Scalar(10, 70, 255);
//    cv::Scalar colorWhite = cv::Scalar(255, 255, 255);

//    //Blank img
//    //CV_8UC3 means 8bits (2^8), unsigned 0 - 255 (signed = -127 - 127), 3
//    color channels
//    //BGR = blue, green, red

//    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
//    //Mat img(512, 512, CV_8UC3, blue);

//    //circle(img,Point(256,256), 155, Scalar(0,70,255),thickness = 10 OR
//    FILLED); circle(img, Point(256, 256), 155, colorOrange, FILLED);

//    //Rectangle
//    //can use option 1, width and height,
//    //option 2, points
//    rectangle(img, Point(130, 226), Point(382, 286), colorWhite, 3);

//    //line
//    //line(img,Point(130, 296), Point(382,296), Scalar(255,255,255), 2);
//    line(img, Point(130, 296), Point(382, 296), colorBlue, 2);

//    putText(img, "Akita's shop", Point(100, 200), FONT_HERSHEY_COMPLEX, 0.5,
//    colorBlue, 2);
//    //Display image
//    imshow("NewLine!", img);

//    // it will close when you open it, so use 0 for infinite delay
//    waitKey(0);
//    return 0;
// }
