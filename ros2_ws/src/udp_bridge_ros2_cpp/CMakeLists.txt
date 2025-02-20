cmake_minimum_required(VERSION 3.8)
project(udp_bridge_ros2_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

SET(EXTRA_LIBS 
    libunitree_legged_sdk.a 
)


# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

# Linking Unitree's SDK's
link_directories(${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/lib/cpp/${ARCH})

# Include SDK's header files
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/include)


add_executable(udp_bridge src/udp_bridge.cpp)
add_executable(examplePublisher src/examplePublisher.cpp)
add_executable(exampleSubscriber src/exampleSubscriber.cpp)


include_directories(include)
target_include_directories(udp_bridge PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(udp_bridge PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

ament_target_dependencies(examplePublisher rclcpp std_msgs)
ament_target_dependencies(exampleSubscriber rclcpp std_msgs)
ament_target_dependencies(udp_bridge rclcpp std_msgs)

install(
  DIRECTORY include 
  ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/include 
  #${CMAKE_SOURCE_DIR}/utils/faceLightSDK_Nano/include
  DESTINATION include
)

install(TARGETS 
  udp_bridge
  examplePublisher
  exampleSubscriber
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
