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

//https://en.cppreference.com/w/cpp/chrono
#include <chrono> // provides system_clock, times and durations

//https://en.cppreference.com/w/cpp/header/functional
#include <functional> // provides the std::bind()

//https://en.cppreference.com/w/cpp/header/memory
#include <memory> // provides std::make_shared<Class>()

//https://en.cppreference.com/w/cpp/header/string
#include <string> // provides std::to_string()
#include <iostream>
#include <unistd.h>

//ROS 2 Specific includes
//https://docs.ros2.org/latest/api/rclcpp/rclcpp_8hpp.html
#include "rclcpp/rclcpp.hpp" // includes most common libraries for ROS 2
//https://index.ros.org/p/std_msgs/
//https://docs.ros.org/en/humble/Concepts/Basic/About-Interfaces.html
#include "std_msgs/msg/u_int32.hpp" // provides basic Unsigned Int32 message type for publishing data

#include "go1_ros2_cpp/msg/led.hpp"


//Important: these includes should be reflected in the package.xml and CMakeLists.txt

//Namespace specified for simplfication when using chrono library
using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

//Declaring a new class as a subclass of the ROS 2 Node class
class ExamplePublisher : public rclcpp::Node
{
public:
  //Constructor, specifying node name and initialising a counter
  ExamplePublisher()
  : Node("example_publisher"), count_(0)
  {
    // Create the instance of the publisher that will publish messages
    // of type go1_ros2_cpp/msgs/LED to the topic "/face/led"
    // a queue length of 10 is specified here for the topic
    publisher_ = this->create_publisher<go1_ros2_cpp::msg::LED>("/face/led", 10);

    // Create a timer that will trigger calls to the method timer_callback
    // every 0.5s
    timer_ = this->create_wall_timer(
      500ms, std::bind(&ExamplePublisher::timer_callback, this));
  }

private:
  // This method will be called automatically by the timer
  // at the specified intervals
  void timer_callback()
  {
    //Create an instance of the LED message type
    auto message = go1_ros2_cpp::msg::LED();

    for (int i = 0; i < 12; i++)
    {
      message.id = i;
      message.r = 255;
      message.g = 160;
      usleep(50000);
      publisher_->publish(message);
    }
    for (int i = 0; i < 12; i++)
    {
      message.id = i;
      message.r = 0;
      message.g = 0;
      usleep(50000);
      publisher_->publish(message);
    }
    
    
  }

  //Declaration of private fields used for timer, publisher and counter
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<go1_ros2_cpp::msg::LED>::SharedPtr publisher_;
  size_t count_;
};

//Main method defining entry point for program
int main(int argc, char * argv[])
{
  //Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  //Create the instance of the Node subclass and 
  // start the spinner with a pointer to the instance
  // This will keep the node running until interupted by ROS or node returns
  rclcpp::spin(std::make_shared<ExamplePublisher>());

  //When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
