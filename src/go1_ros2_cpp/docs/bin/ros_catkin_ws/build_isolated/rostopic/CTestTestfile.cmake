# CMake generated Testfile for 
# Source directory: /home/pi/ros_catkin_ws/src/ros_comm/rostopic
# Build directory: /home/pi/ros_catkin_ws/build_isolated/rostopic
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_rostopic_rostest_test_rostopic.test "/home/pi/ros_catkin_ws/build_isolated/rostopic/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/pi/ros_catkin_ws/build_isolated/rostopic/test_results/rostopic/rostest-test_rostopic.xml" "--return-code" "/usr/bin/python2 /home/pi/ros_catkin_ws/install_isolated/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/pi/ros_catkin_ws/src/ros_comm/rostopic --package=rostopic --results-filename test_rostopic.xml --results-base-dir \"/home/pi/ros_catkin_ws/build_isolated/rostopic/test_results\" /home/pi/ros_catkin_ws/src/ros_comm/rostopic/test/rostopic.test ")
set_tests_properties(_ctest_rostopic_rostest_test_rostopic.test PROPERTIES  _BACKTRACE_TRIPLES "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/pi/ros_catkin_ws/install_isolated/share/rostest/cmake/rostest-extras.cmake;52;catkin_run_tests_target;/home/pi/ros_catkin_ws/src/ros_comm/rostopic/CMakeLists.txt;13;add_rostest;/home/pi/ros_catkin_ws/src/ros_comm/rostopic/CMakeLists.txt;0;")
subdirs("gtest")
