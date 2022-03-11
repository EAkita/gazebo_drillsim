#include <ros/ros.h>
#include <std_msgs/String.h>

// argc and argv grab our commandline parameters

int main(int argc, char** argv) {
  // initialize ros system
  ros::init(argc, argv, "talker");  // default name for node

  // object from the roscpp library to be primary interction point with the
  // library
  ros::NodeHandle node_handle;

  // create a publisher
  // specify the kind of msg associated with this published topic
  // specify queue size; 1 = most recent, usually btn 1 and 10, so you can hold
  // some msgs and wait
  // but not wasting memory on msgs you don't care about, from network issue
  ros::Publisher publisher =
      node_handle.advertise<std_msgs::String>("talker_topic", 1);

  // dont' want to spam the system with this "hello" msg, so control the rate
  ros::Rate rate(10);  // 10 hz, 10 msgs/sec
  // Same as this      ros::Rate loop_rate(10);
  // loop to publish the msgs with iteration
  // use helper function ros:: ok to check that

  while (ros::ok())  // true, keep running, user interrupts, = false, then stop
  {
    // create new msg
    std_msgs::String msg;
    msg.data = "Hi boo boo!";

    // use the publisher object and give msg to publish
    publisher.publish(msg);

    // ros is running an event system; give it a chance to update that event
    // system for every while loop, ros has a chance to take care any event
    // before next iteration
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}
