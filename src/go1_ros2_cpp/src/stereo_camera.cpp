// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// PHS: Original file obtained from: https://raw.githubusercontent.com/ros2/examples/humble/rclcpp/topics/minimal_publisher/member_function.cpp 18th Sept 2023, 11:36
// PHS: File renamed from publisher_member_function.cpp
// PHS: Renamed class from MinimalPublisher
// PHS: Additional comments added to document the code
// PHS: Modified topic name used
// HAB75: Modified to stereo_camera nodes for Unitree Go1

// https://en.cppreference.com/w/cpp/chrono
#include <chrono> // provides system_clock, times and durations

// https://en.cppreference.com/w/cpp/header/functional
#include <functional> // provides the std::bind()

// https://en.cppreference.com/w/cpp/header/memory
#include <memory> // provides std::make_shared<Class>()

// https://en.cppreference.com/w/cpp/header/string
#include <string> // provides std::to_string()

// ROS 2 Specific includes
// https://docs.ros2.org/latest/api/rclcpp/rclcpp_8hpp.html
#include "rclcpp/rclcpp.hpp" // includes most common libraries for ROS 2
// https://index.ros.org/p/std_msgs/
// https://docs.ros.org/en/humble/Concepts/Basic/About-Interfaces.html
#include "sensor_msgs/msg/point_cloud2.hpp" // Point cloud message from cameras

// Important: these includes should be reflected in the package.xml and CMakeLists.txt
#include "UnitreeCameraSDK.hpp"

// Namespace specified for simplfication when using chrono library
using namespace std::chrono_literals;
using namespace cv; // Open CV namespace, Added for same reasons above.

// UnitreeCamera StereoCamera object
UnitreeCamera camera("../sdk/UnitreecameraSDK/stereo_camera_config.yaml"); // Unitree Go1 head-front camera

/* This program creates a node for outputting image data from the Go1 stereo cameras
   That will include point cloud data & raw image data */

// Declaring a new class as a subclass of the ROS 2 Node class
class CameraPublisher : public rclcpp::Node
{
public:
  // Constructor, specifying node name and initialising a counter
  CameraPublisher()
      : Node("CameraSDK"), count_(0)
  {

    // Create the instance of the publisher that will publish messages
    // of type std_msgs/mgs/UInt32 to the topic "/hello/world"
    // a queue length of 10 is specified here for the topic
    publisher_PCPrototype = this->create_publisher<sensor_msgs::msg::PointCloud2>("/sensors/camera/face_camera/image_pointcloud", 10);

    // Create a timer that will trigger calls to the method timer_callback
    // every 0.5s
    timer_ = this->create_wall_timer(
        100ms, std::bind(&CameraPublisher::timer_callback, this));
  }

private:
  // This method will be called automatically by the timer
  // at the specified intervals
  void timer_callback()
  {
    // Create an instance of the UInt32 message type
    auto message = sensor_msgs::msg::PointCloud2();

    // SDK PointCloud raw data with points
    std::vector<PCLType> pointCloud_RAW;
    // Raw data timestamp
    std::chrono::microseconds timestamp;
    // Capture raw data
    try
    {
      camera.getPointCloud(pointCloud_RAW, timestamp);
    } // If theres an error, Throw error to ros output terminal
    catch (const std::exception &e)
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to get point cloud: %s", e.what());
    }
    catch (...)
    {
      RCLCPP_ERROR(this->get_logger(), "Unknown error occurred while getting point cloud.");
    }


    // set timestamp from ros internal clock
    // source from: https://docs.ros.org/en/foxy/Tutorials/Intermediate/Tf2/Learning-About-Tf2-And-Time-Cpp.html
    message.header.stamp = this->get_clock()->now();
    message.header.frame_id = "face_camera";

    // // Set dimensions
    // message.width = 928; // From YAML FrameSize. No idea how to have this set by the YAML file..
    // message.height = 400;
    // message.is_dense = false;
    // message.is_bigendian = false;

    message.height = 1;
    message.width = pointCloud_RAW.size();
    message.is_dense = false;
    message.is_bigendian = false;
    message.point_step = 16;
    message.row_step = message.point_step * message.width;
    message.data.resize(message.row_step);

    uint8_t *ptr = message.data.data();
    for (const auto &pt : pointCloud_RAW)
    {
      float x = pt.pts[0];
      float y = pt.pts[1];
      float z = pt.pts[2];
      uint8_t r = pt.clr[2];
      uint8_t g = pt.clr[1];
      uint8_t b = pt.clr[0];

      uint32_t rgb_packed = (r << 16) | (g << 8) | (b);
      float rgb_float;
      std::memcpy(&rgb_float, &rgb_packed, sizeof(float));

      std::memcpy(ptr, &x, sizeof(float));
      std::memcpy(ptr + 4, &y, sizeof(float));
      std::memcpy(ptr + 8, &z, sizeof(float));
      std::memcpy(ptr + 12, &rgb_float, sizeof(float));

      ptr += message.point_step;
    }

    // Add ROS 2 logger entry with details of the message (print message to console)
    // RCLCPP_INFO(this->get_logger(), "Publishing: msg.data=%i", message.data);

    // publish the message created above to the topic /hello/world
    publisher_PCPrototype->publish(message);
  }

  // Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_PCPrototype;
  size_t count_;
};

// Main method defining entry point for program
int main(int argc, char *argv[])
{
  // Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  // Create the instance of the Node subclass and
  //  start the spinner with a pointer to the instance
  //  This will keep the node running until interupted by ROS or node returns
  rclcpp::spin(std::make_shared<CameraPublisher>());

  // When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
