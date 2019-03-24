/** @file demo_flight_control.cpp
 *  @version 3.3
 *  @date May, 2017
 *
 *  @brief
 *  demo sample of how to use flight control APIs
 *
 *  @copyright 2017 DJI. All rights reserved.
 *
 */

#include <thread>
#include <sensor_msgs/Joy.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Pose.h>
#include <ImageProcess.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "demo_flight_control_node");
  ros::NodeHandle nh;

  ImageProcess* imgprocessor = new ImageProcess();

  // Subscribe to messages from dji_sdk_node
  ros::Subscriber fimgSub = nh.subscribe("/forwardimg", 10, &ImageProcess::forward_image_callback_simple, imgprocessor);
  std::thread imgLoopThread(&ImageProcess::img_loop, imgprocessor);

  ros::spin();
  
  return 0;
}

