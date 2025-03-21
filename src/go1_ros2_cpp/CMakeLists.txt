# A CMake file for a Ros interface to the unitree Go1
# Auther: Harry Bowker (Hab75) / OmniaUK @ Github
# Version 1.0
# Source used: https://docs.ros.org/en/humble/How-To-Guides/Ament-CMake-Documentation.html
#              With legged_sdk CMake used as additional resource.


# check arch and os 
# from SDK CMake file (NOT IN USE)
# message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
# if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64.*")
#   set(ARCH amd64)
# endif()
# if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "aarch64.*")
#   set(ARCH arm64)
# endif()


cmake_minimum_required(VERSION 3.8)
project(go1_ros2_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

#
# Install .msg
#
# .msg Includes Source: https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Custom-ROS2-Interfaces.html
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/BmsCmd.msg"
  "msg/BmsState.msg"
  "msg/Cartesian.msg"
  "msg/HighCmd.msg"
  "msg/HighState.msg"
  "msg/IMU.msg"
  "msg/LED.msg"
  "msg/LowCmd.msg"
  "msg/LowState.msg"
  "msg/MotorState.msg"
  "msg/MotorCmd.msg"
  DEPENDENCIES # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
)
rosidl_get_typesupport_target(cpp_typesupport_target "${PROJECT_NAME}" "rosidl_typesupport_cpp")


#
# Linking Unitree's SDK's
#
link_directories(${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/lib/cpp/amd64)
link_directories(${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/lib)
link_directories(${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/lib/amd64)

#
# Include SDK's header files
#
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/include)
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/include)
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/include)

SET(LEGGED_LIB ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/lib/cpp/amd64/libunitree_legged_sdk.a)
SET(FACELED_LIB ${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/lib/libfaceLight_SDK_amd64.so)
SET(CAMERA_LIB ${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/lib/amd64/libunitree_camera.a)

#
# Create executables
#
add_executable(udp_bridge src/udp_bridge.cpp)
add_executable(legged_udp_rx src/legged_udp_rx.cpp)
add_executable(face_light_controller src/face_light_controller.cpp)
add_executable(twist_subscriber src/twist_subscriber.cpp)

#
# Set dependacies
#
ament_export_dependencies(rosidl_default_runtime) # msg export
ament_target_dependencies(udp_bridge rclcpp std_msgs)

ament_target_dependencies(legged_udp_rx rclcpp std_msgs)
ament_target_dependencies(face_light_controller rclcpp std_msgs)

ament_target_dependencies(twist_subscriber rclcpp std_msgs geometry_msgs)

# Install includes before packages
install(
  DIRECTORY include 
  ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/include 
  ${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/include
  ${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/include
  DESTINATION include
)

#
# Install executables to package
#
install(TARGETS 
  udp_bridge
  legged_udp_rx
  twist_subscriber
  face_light_controller
  DESTINATION lib/${PROJECT_NAME})


#
# Install SDK's
#
target_link_libraries(udp_bridge
  ${LEGGED_LIB}
  ${FACELED_LIB}
  pthread
  rt
)

target_link_libraries(legged_udp_rx
  ${LEGGED_LIB} #legged SDK
  ${FACELED_LIB} # Facelight SDK
  "${cpp_typesupport_target}" # msg include
  pthread
  rt
)

target_link_libraries(twist_subscriber
  ${LEGGED_LIB} #Legged include only
  pthread
  rt
)

target_link_libraries(face_light_controller
  ${FACELED_LIB} # Face LED SDK
  "${cpp_typesupport_target}" # msg include
  pthread
  rt
)





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
