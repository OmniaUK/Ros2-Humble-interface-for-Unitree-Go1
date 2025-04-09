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
// Hab75: Modified topic name and use to legged_controller for Unitree Go1.

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
#include "geometry_msgs/msg/twist.hpp" // twist msg

// Unitree ros to real msg's
// Edited to comply with syntax constraints.
#include "go1_ros2_cpp/msg/bms_state.hpp"
#include "go1_ros2_cpp/msg/high_state.hpp"
#include "go1_ros2_cpp/msg/high_cmd.hpp"
#include "go1_ros2_cpp/msg/imu.hpp"

// Important: these includes should be reflected in the package.xml and CMakeLists.txt

// UnitreeSDK includes
/*IMPORTANT SOURCE: https://unitree-docs.readthedocs.io/en/latest/get_started/Go1_Edu.html*/
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
class LeggedDataRX : public rclcpp::Node
{

public:
  // Constructor, specifying node name and initialising a counter
  LeggedDataRX()
      : Node("LeggedDataRX"), count_(0)
  {
    // Create the instance of the publisher that will publish messages
    // of type go1_ros2_cpp/msg/bms_state to the topic "/legged_data/bms"
    // a queue length of 10 is specified here for the topic
    bms_publisher = this->create_publisher<go1_ros2_cpp::msg::BmsState>("/legged_data/sensors/bms", 10);
    // Create a timer that will trigger calls to the method bms_callback
    // every 0.65s
    timer_bms = this->create_wall_timer(
        650ms, std::bind(&LeggedDataRX::bms_callback, this));

    // Create the instance of the publisher that will publish messages
    // of type go1_ros2_cpp/msg/high_state to the topic "/legged_data/bms"
    // a queue length of 10 is specified here for the topic
    foot_force_publisher = this->create_publisher<go1_ros2_cpp::msg::HighState>("/legged_data/sensors/foot_force", 10);
    // Create a timer that will trigger calls to the method footForce_callback
    // every 0.15s
    timer_foot_force = this->create_wall_timer(
        150ms, std::bind(&LeggedDataRX::footForce_callback, this));

    // Create the instance of the publisher that will publish messages
    // of type go1_ros2_cpp/msg/imu to the topic "/legged_data/sensors/imu"
    // a queue length of 10 is specified here for the topic
    imu_publisher = this->create_publisher<go1_ros2_cpp::msg::IMU>("/legged_data/sensors/imu", 10);
    // Create a timer that will trigger calls to the method imu_callback
    // every 0.05s
    timer_imu = this->create_wall_timer(
        50ms, std::bind(&LeggedDataRX::imu_callback, this));

    // Create the instance of the publisher that will publish messages
    // of type go1_ros2_cpp/msg/imu to the topic "/legged_data/status/mode"
    // a queue length of 10 is specified here for the topic
    mode_publisher = this->create_publisher<go1_ros2_cpp::msg::HighState>("/legged_data/status/mode", 10);
    // Create a timer that will trigger calls to the method imu_callback
    // every 0.65s
    timer_mode = this->create_wall_timer(
        650ms, std::bind(&LeggedDataRX::mode_callback, this));
  }

private:
  /*
   * BMS Data publisher
   * Takes bms data and updates the msg with latest battery sensor data
   * WARNING: Batterys will require to be on compatable firmware versions to the robot for data.
   */
  void bms_callback()
  {
    // Create an instance of the BmsState message type
    auto message = go1_ros2_cpp::msg::BmsState();

    udpLegged.UDPSend();
    udpLegged.UDPRecv(); // Fetch the latest state

    // Convert UDP_Raw to BmsState
    message.soc = udpLegged.state.bms.SOC;               // Battery %
    message.current = udpLegged.state.bms.current;       // current in milliamp
    message.cell_vol = udpLegged.state.bms.cell_vol;     // cell voltage in array[10]
    message.version_h = udpLegged.state.bms.version_h;   // Battery firmware version
    message.bms_status = udpLegged.state.bms.bms_status; // Battery status
    message.cycle = udpLegged.state.bms.cycle;           // The current number of cycles of the battery
    message.bq_ntc = udpLegged.state.bms.BQ_NTC;         // Temp output in degrees C
    message.mcu_ntc = udpLegged.state.bms.MCU_NTC;       // Temp output in degrees C

    // Check if the battery is reporting data
    if (message.soc == 0)
    {
      // If no battery data is detected, display error warning
      RCLCPP_WARN(this->get_logger(), "WARNING: Battery Management System \n Data: OutOfExpectedBounds: Please ensure a healthy battery is installed OR of a compatable firmware \n Low battery safe shutdown: Offline");
    }

    // Remove on release
    RCLCPP_INFO(this->get_logger(), "Battery at: %i%%", message.soc);

    // publish the message created above to the topic /legged_data/sensors/bms
    bms_publisher->publish(message);
  }
  // Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_bms;
  rclcpp::Publisher<go1_ros2_cpp::msg::BmsState>::SharedPtr bms_publisher;

  /*
   * FootForce Data publisher
   * Takes HighState data and updates the msg with latest foot force sensor data
   */
  void footForce_callback()
  {
    // Create an instance of the HighState message type
    auto message = go1_ros2_cpp::msg::HighState();

    udpLegged.UDPSend();
    udpLegged.UDPRecv(); // Fetch the latest state

    message.foot_force = udpLegged.state.footForce;
    message.foot_force_est = udpLegged.state.footForceEst;

    // Remove on release
    RCLCPP_INFO(this->get_logger(), "foot pressure: %d, %d, %d, %d", message.foot_force[0],
                message.foot_force[1], message.foot_force[2], message.foot_force[3]);

    // publish the message created above to the topic /legged_data/sensors/foot_force
    foot_force_publisher->publish(message);
  }

  // Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_foot_force;
  rclcpp::Publisher<go1_ros2_cpp::msg::HighState>::SharedPtr foot_force_publisher;

  /*
   * IMU Data publisher
   * Takes IMU data and updates the msg with latest imu data
   */
  void imu_callback()
  {
    // Create an instance of the IMU message type
    auto message = go1_ros2_cpp::msg::IMU();

    udpLegged.UDPSend();
    udpLegged.UDPRecv(); // Fetch the latest state

    message.quaternion = udpLegged.state.imu.quaternion;
    message.gyroscope = udpLegged.state.imu.gyroscope;
    message.accelerometer = udpLegged.state.imu.accelerometer;
    message.rpy = udpLegged.state.imu.rpy;
    message.temperature = udpLegged.state.imu.temperature;

    // Remove on release
    RCLCPP_INFO(this->get_logger(), "System Temp(C): %i", message.temperature);

    // publish the message created above to the topic /legged_data/sensors/imu
    imu_publisher->publish(message);
  }

  // Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_imu;
  rclcpp::Publisher<go1_ros2_cpp::msg::IMU>::SharedPtr imu_publisher;

  /*
   * Mode Data publisher
   * Takes HighState data and updates the msg with latest mode data
   */
  void mode_callback()
  {
    // Create an instance of the HighState message type
    auto message = go1_ros2_cpp::msg::HighState();

    udpLegged.UDPSend();
    udpLegged.UDPRecv(); // Fetch the latest state

    // Set latest known mode to msg
    message.mode = udpLegged.state.mode;

    // Remove on release
    RCLCPP_INFO(this->get_logger(), "System mode: %i", message.mode);

    // publish the message created above to the topic /legged_data/status/mode
    mode_publisher->publish(message);
  }

  // Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_mode;
  rclcpp::Publisher<go1_ros2_cpp::msg::HighState>::SharedPtr mode_publisher;

  size_t count_;
};

// Declaring a new class as a subclass of the ROS 2 Node class
class LeggedControl : public rclcpp::Node
{
public:
  // Constructor specifying node name for superclass
  LeggedControl()
      : Node("legged_control")
  {

    // Create the instance of the twist subscriber that will receive messages
    // of type geometry_msgs::msg::Twist published to the topic "/cmd_vel"
    // a queue length of 10 is specified here and a reference is given
    subscription_twist = this->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", 10, std::bind(&LeggedControl::twist_callback, this, std::placeholders::_1));

    // Create the instance of the mode subscriber that will receive messages
    // of type  published to the topic "/cmd_mode"
    // a queue length of 10 is specified here and a reference is given
    subscription_mode = this->create_subscription<go1_ros2_cpp::msg::HighCmd>(
        "/cmd_mode", 10, std::bind(&LeggedControl::cmdMode_callback, this, std::placeholders::_1));
  }

private:
  /*
   * twist Data subscriber
   * Takes twist msg data and sends it via UDP to the robot
   */
  void twist_callback(const geometry_msgs::msg::Twist &msg)
  {
    // Logger used to print details of the message received (printed to console).
    RCLCPP_INFO(this->get_logger(), "I heard: msg.data=%f  and  %f", msg.linear.x, msg.angular.z);
    udpLegged.cmd.velocity[0] = msg.linear.x; // Forward / backward motion
    udpLegged.cmd.velocity[1] = msg.linear.y; // Left / right motion

    udpLegged.cmd.bodyHeight = msg.linear.z; // Vertical height

    udpLegged.cmd.yawSpeed = msg.angular.z; // Rotation in rad/s

    udpLegged.udp.SetSend(udpLegged.cmd);
    udpLegged.UDPSend();
  }
  // Declaration of private fields used for subscriber
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_twist;

  /*
   * mode Data subscriber
   * Takes HighCmd msg data and sends it via UDP to the robot
   */
  void cmdMode_callback(const go1_ros2_cpp::msg::HighCmd &msg)
  {

    // Remove on release
    RCLCPP_INFO(this->get_logger(), "I heard: msg.data=%i", msg.mode);

    udpLegged.cmd.mode = msg.mode;

    udpLegged.udp.SetSend(udpLegged.cmd);
    udpLegged.UDPSend();
  }
  // Declaration of private fields used for subscriber
  rclcpp::Subscription<go1_ros2_cpp::msg::HighCmd>::SharedPtr subscription_mode;
};

// Main method defining entry point for program
int main(int argc, char *argv[])
{
  // Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  /*
   * Start node as multithread process
   * Prevents any single callback blocking another. (Helps improve performance)
   * Source: https://docs.ros.org/en/humble/Concepts/Intermediate/About-Executors.html
   */
  rclcpp::executors::MultiThreadedExecutor executor;
  auto leggedDataNode = std::make_shared<LeggedDataRX>();
  auto LeggedControlNode = std::make_shared<LeggedControl>();
  executor.add_node(leggedDataNode);
  executor.add_node(LeggedControlNode);
  executor.spin();

  // When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
