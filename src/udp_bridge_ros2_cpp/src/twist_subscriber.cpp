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
#include "geometry_msgs/msg/twist.hpp"  // twist msg

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

UDPLegged udpLegged(HIGHLEVEL); // Global object creation

//Declaring a new class as a subclass of the ROS 2 Node class
class TwistSubscriber : public rclcpp::Node
{
public:
  //Constructor specifying node name for superclass
  TwistSubscriber()
  : Node("twist_subscriber")
  {
    udpLegged.cmd.mode = 0; // 0:idle, default stand      1:forced stand     2:walk continuously
    udpLegged.cmd.gaitType = 0;
    udpLegged.cmd.speedLevel = 0;
    udpLegged.cmd.footRaiseHeight = 0;
    udpLegged.cmd.bodyHeight = 0;
    udpLegged.cmd.euler[0] = 0;
    udpLegged.cmd.euler[1] = 0;
    udpLegged.cmd.euler[2] = 0;
    udpLegged.cmd.velocity[0] = 0.0f;
    udpLegged.cmd.velocity[1] = 0.0f;
    udpLegged.cmd.yawSpeed = 0.0f;
    udpLegged.cmd.reserve = 0;
    // Create the instance of the subscriber that will receive messages
    // of type std_msgs/mgs/UInt32 published to the topic "/hello/world"
    // a queue length of 10 is specified here and a reference is given
    // to the topic_callback method that will process messages that are received.
    subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel", 10, std::bind(&TwistSubscriber::twist_callback, this, std::placeholders::_1));
  }

private:
  // Private function that will be triggered automatically when messages are received
  // from the topic /cmd_vel
  // The parameter specifies the expected message type, which must match
  // the type published to the topic
  void twist_callback(const geometry_msgs::msg::Twist & msg)
  {
    //Logger used to print details of the message received (printed to console).
    RCLCPP_INFO(this->get_logger(), "I heard: msg.data=%f  and  %f", msg.linear.x, msg.angular.z);
    udpLegged.cmd.velocity[0] = msg.linear.x;  // Forward / backward motion
    udpLegged.cmd.velocity[1] = msg.linear.y; // Left / right motion

    udpLegged.cmd.bodyHeight = msg.linear.z; // Vertical height

    udpLegged.cmd.yawSpeed = msg.angular.z; // Rotation in rad/s

    udpLegged.cmd.mode = 2;

    udpLegged.udp.SetSend(udpLegged.cmd);
  }

  //Declaration of private fields used for subscriber
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};











// Main method defining entry point for program
int main(int argc, char *argv[])
{
  // Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  // High speed looping updates for tx & rx
  LoopFunc loop_udpSend("udp_send", udpLegged.dt, 3, boost::bind(&UDPLegged::UDPSend, &udpLegged));
  LoopFunc loop_udpRecv("udp_recv", udpLegged.dt, 3, boost::bind(&UDPLegged::UDPRecv, &udpLegged));

  loop_udpSend.start();
  loop_udpRecv.start();

  // Create the instance of the Node subclass and
  //  start the spinner with a pointer to the instance
  //  This will keep the node running until interupted by ROS or node returns
  rclcpp::spin(std::make_shared<TwistSubscriber>());

  // When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
