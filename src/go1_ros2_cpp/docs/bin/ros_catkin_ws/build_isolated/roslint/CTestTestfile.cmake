# CMake generated Testfile for 
# Source directory: /home/pi/ros_catkin_ws/src/roslint
# Build directory: /home/pi/ros_catkin_ws/build_isolated/roslint
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_roslint_roslint_package "/home/pi/ros_catkin_ws/build_isolated/roslint/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/pi/ros_catkin_ws/build_isolated/roslint/test_results/roslint/roslint-roslint.xml" "--working-dir" "/home/pi/ros_catkin_ws/build_isolated/roslint" "--return-code" "/home/pi/ros_catkin_ws/src/roslint/scripts/test_wrapper /home/pi/ros_catkin_ws/build_isolated/roslint/test_results/roslint/roslint-roslint.xml make roslint_roslint")
set_tests_properties(_ctest_roslint_roslint_package PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/melodic/share/catkin/cmake/test/tests.cmake;143;add_test;/home/pi/ros_catkin_ws/build_isolated/roslint/cmake/roslint-extras.cmake;67;catkin_run_tests_target;/home/pi/ros_catkin_ws/src/roslint/CMakeLists.txt;31;roslint_add_test;/home/pi/ros_catkin_ws/src/roslint/CMakeLists.txt;0;")
subdirs("gtest")
