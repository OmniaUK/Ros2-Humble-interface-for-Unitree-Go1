# check arch and os 
# from SDK CMake file
message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64.*")
  set(ARCH amd64)
endif()
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "aarch64.*")
  set(ARCH arm64)
endif()

cmake_minimum_required(VERSION 3.8)
project(udp_bridge_ros2_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

SET(EXTRA_LIBS ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/lib/cpp/amd64/libunitree_legged_sdk.a)



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

# Linking Unitree's SDK's
link_directories(${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/lib/cpp/amd64)
link_directories(${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/lib)
link_directories(${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/lib/amd64)

# Include SDK's header files
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/include)
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/include)
include_directories(include ${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/include)


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

# Install includes before packages
install(
  DIRECTORY include 
  ${CMAKE_SOURCE_DIR}/sdk/unitree_legged_sdk/include 
  ${CMAKE_SOURCE_DIR}/sdk/faceLightSDK_Nano/include
  ${CMAKE_SOURCE_DIR}/sdk/UnitreecameraSDK/include
  DESTINATION include
)

install(TARGETS 
  udp_bridge
  examplePublisher
  exampleSubscriber
  DESTINATION lib/${PROJECT_NAME})


target_link_libraries(udp_bridge
  ${EXTRA_LIBS}
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
