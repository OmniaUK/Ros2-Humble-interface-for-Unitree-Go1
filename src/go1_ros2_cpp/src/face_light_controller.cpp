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

// PHS: Original file obtained from: wget -O subscriber_member_function.cpp https://raw.githubusercontent.com/ros2/examples/humble/rclcpp/topics/minimal_subscriber/member_function.cpp 18 Sept, 14:45
// PHS: File renamed from subscriber_member_function.cpp
// PHS: Renamed class from MinimalSubscriber
// PHS: Additional comments added to document the code
// PHS: Modified topic name used
// HAB75: Edit template to face_light_controller subscriber

//General C++ includes as needed
#include <chrono>
#include <functional>
#include <memory>
#include <string>

//ROS 2 Specific includes
//Important: these includes should be reflected in the package.xml and CMakeLists.txt
#include "rclcpp/rclcpp.hpp"

// UnitreeSDK includes
/*IMPORTANT SOURCE: https://unitree-docs.readthedocs.io/en/latest/get_started/Go1_Edu.html*/
#include "FaceLightClient.h"

// Custom msg type includes
#include "go1_ros2_cpp/msg/led.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/* Template giving outline for creating a program
 * that contains both a publisher and subscriber.
 */

FaceLightClient ledClient;

class FaceLightController : public rclcpp::Node
{
public:
  //Constructor specifying node name for superclass
  FaceLightController()
  : Node("face_light_controller")
  {
    // Create the instance of the subscriber that will receive messages
    // of type go1_ros2_cpp/msg/led published to the topic "/hello/world"
    // a queue length of 10 is specified here and a reference is given
    // to the topic_callback method that will process messages that are received.
    faceLight_subscription = this->create_subscription<go1_ros2_cpp::msg::LED>(
      "face/led", 10, std::bind(&FaceLightController::topic_callback, this, _1));
  }

private:
  // Private function that will be triggered automatically when messages are received
  // from the topic /hello/world
  // The parameter specifies the expected message type, which must match
  // the type published to the topic
  void topic_callback(const go1_ros2_cpp::msg::LED & msg)
  {
    uint8_t rgb[3] = {msg.r, msg.g, msg.b};
    ledClient.setLedColor(msg.id, rgb); // Set colour
    ledClient.sendCmd();

    // Remove on release
    RCLCPP_INFO(this->get_logger(), "Setting r=%i, g=%i, b=%i  - On LED: %i", msg.r, msg.g, msg.b, msg.id);
  }

  //Declaration of private fields used for subscriber
  rclcpp::Subscription<go1_ros2_cpp::msg::LED>::SharedPtr faceLight_subscription;
};

//Main method defining entry point for program
int main(int argc, char * argv[])
{
  //Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  //Create the instance of the Node subclass and 
  // start the spinner with a pointer to the instance
  rclcpp::spin(std::make_shared<FaceLightController>());

  //When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
