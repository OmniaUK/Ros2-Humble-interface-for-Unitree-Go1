# CMake generated Testfile for 
# Source directory: /home/pi/ros_catkin_ws/src/ros_comm/roslz4
# Build directory: /home/pi/ros_catkin_ws/build_isolated/roslz4
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_roslz4_gtest_test_roslz4 "/home/pi/ros_catkin_ws/build_isolated/roslz4/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/pi/ros_catkin_ws/build_isolated/roslz4/test_results/roslz4/gtest-test_roslz4.xml" "--return-code" "/home/pi/ros_catkin_ws/devel_isolated/roslz4/lib/roslz4/test_roslz4 --gtest_output=xml:/home/pi/ros_catkin_ws/build_isolated/roslz4/test_results/roslz4/gtest-test_roslz4.xml")
set_tests_properties(_ctest_roslz4_gtest_test_roslz4 PROPERTIES  _BACKTRACE_TRIPLES "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/gtest.cmake;89;catkin_run_tests_target;/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/gtest.cmake;28;_catkin_add_google_test;/home/pi/ros_catkin_ws/src/ros_comm/roslz4/CMakeLists.txt;84;catkin_add_gtest;/home/pi/ros_catkin_ws/src/ros_comm/roslz4/CMakeLists.txt;0;")
subdirs("gtest")
