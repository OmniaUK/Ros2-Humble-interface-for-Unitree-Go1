# CMake generated Testfile for 
# Source directory: /home/pi/ros_catkin_ws/src/pcl_conversions
# Build directory: /home/pi/ros_catkin_ws/build_isolated/pcl_conversions
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_pcl_conversions_gtest_test_pcl_conversions "/home/pi/ros_catkin_ws/build_isolated/pcl_conversions/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/pi/ros_catkin_ws/build_isolated/pcl_conversions/test_results/pcl_conversions/gtest-test_pcl_conversions.xml" "--return-code" "/home/pi/ros_catkin_ws/devel_isolated/pcl_conversions/lib/pcl_conversions/test_pcl_conversions --gtest_output=xml:/home/pi/ros_catkin_ws/build_isolated/pcl_conversions/test_results/pcl_conversions/gtest-test_pcl_conversions.xml")
set_tests_properties(_ctest_pcl_conversions_gtest_test_pcl_conversions PROPERTIES  _BACKTRACE_TRIPLES "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/gtest.cmake;89;catkin_run_tests_target;/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/gtest.cmake;28;_catkin_add_google_test;/home/pi/ros_catkin_ws/src/pcl_conversions/CMakeLists.txt;43;catkin_add_gtest;/home/pi/ros_catkin_ws/src/pcl_conversions/CMakeLists.txt;0;")
subdirs("gtest")
