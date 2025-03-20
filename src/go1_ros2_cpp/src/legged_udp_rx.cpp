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
// Hab75: Modified topic name and use.

/*
About: A Ros publisher file that takes recived UDP data from a unitree Go1 to publush
*/

// https://en.cppreference.com/w/cpp/chrono
#include <chrono> // provides system_clock, times and durations

// https://en.cppreference.com/w/cpp/header/functional
#include <functional> // provides the std::bind()

// https://en.cppreference.com/w/cpp/header/memory
#include <memory> // provides std::make_shared<Class>()

// https://en.cppreference.com/w/cpp/header/string
#include <string> // provides std::to_string()

// General includes
#include <math.h>
#include <iostream>
#include <unistd.h>

// ROS 2 Specific includes
// https://docs.ros2.org/latest/api/rclcpp/rclcpp_8hpp.html
#include "rclcpp/rclcpp.hpp" // includes most common libraries for ROS 2
// https://index.ros.org/p/std_msgs/
// https://docs.ros.org/en/humble/Concepts/Basic/About-Interfaces.html
#include "std_msgs/msg/u_int8.hpp" // provides basic Unsigned Int32 message type for publishing data
#include "go1_ros2_cpp/msg/bms_state.hpp"

// Important: these includes should be reflected in the package.xml and CMakeLists.txt

// UnitreeSDK includes
#include "unitree_legged_sdk/unitree_legged_sdk.h"

// IP Address to Pi   (Default: WiFi - 192.168.12.1,   Ethernet - 192.168.123.161)
const char *piAddress = "192.168.12.1";

// Namespace specified for simplfication when using chrono library
using namespace UNITREE_LEGGED_SDK;
using namespace std::chrono_literals;

/* Legged SDK UDP initializer class.
This class sets up a UDP connection to the robot.
Code sourced & modified from exampleWalk in the unitree_legged_sdk/examples
*/
class UDPLegged
{
public: // <- Change to your robot model- Aliengo, A1, Go1 (Tested), B1
  UDPLegged(uint8_t level) : safe(LeggedType::Go1), 
                udp(level, 8090, "192.168.12.1", 8082)
  {
    udp.InitCmdData(cmd);
  }
  void UDPRecv();
  void UDPSend();

  Safety safe;
  UDP udp;
  HighCmd cmd = {}; // Left
  HighState state = {};
  float dt = 0.002; // 0.001~0.01
};

void UDPLegged::UDPRecv()
{
  udp.Recv();
  udp.GetRecv(state);
}

void UDPLegged::UDPSend()
{
  udp.Send();
}

UDPLegged udpLegged(HIGHLEVEL); // object creation for callback






// Declaring a new class as a subclass of the ROS 2 Node class
class BMSPublisher : public rclcpp::Node
{

public:
  // Constructor, specifying node name and initialising a counter
  BMSPublisher()
      : Node("bms_publisher"), count_(0)
  {
    // Create the instance of the publisher that will publish messages
    // of type std_msgs/mgs/UInt32 to the topic "/hello/world"
    // a queue length of 10 is specified here for the topic
    publisher_ = this->create_publisher<go1_ros2_cpp::msg::BmsState>("/legged_data/bms", 10);

    // Create a timer that will trigger calls to the method timer_callback
    // every 0.5s
    timer_ = this->create_wall_timer(
        500ms, std::bind(&BMSPublisher::bms_callback, this));
  }

private:
  // This method will be called automatically by the timer
  // at the specified intervals
  void bms_callback()
  {
    // Create an instance of the UInt8 message type
    auto message = go1_ros2_cpp::msg::BmsState();

    // Set the pre-defined field "data" in the message to a positive integer value,
    //message.data = udpLegged.state.bms.SOC;
    message.soc = udpLegged.state.bms.SOC;

    // custom.UDPRecv(); // Update state from legged SDK
    RCLCPP_INFO(this->get_logger(), "Battery at %i", message.soc);

    // publish the message created above to the topic /legged_data/rx/bms
    publisher_->publish(message);
  }

  // Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<go1_ros2_cpp::msg::BmsState>::SharedPtr publisher_;
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
  // rclcpp::executors::SingleThreadedExecutor executor;
  // executor.add_node(std::make_shared<BMSPublisher>());
  // executor.spin();
  rclcpp::spin(std::make_shared<BMSPublisher>());
  

  // When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
