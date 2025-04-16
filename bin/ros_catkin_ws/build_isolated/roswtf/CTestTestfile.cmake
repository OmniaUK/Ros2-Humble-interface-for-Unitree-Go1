# CMake generated Testfile for 
# Source directory: /home/pi/ros_catkin_ws/src/ros_comm/roswtf
# Build directory: /home/pi/ros_catkin_ws/build_isolated/roswtf
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_roswtf_rostest_test_roswtf.test "/home/pi/ros_catkin_ws/build_isolated/roswtf/catkin_generated/env_cached.sh" "/usr/bin/python2" "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/run_tests.py" "/home/pi/ros_catkin_ws/build_isolated/roswtf/test_results/roswtf/rostest-test_roswtf.xml" "--return-code" "/usr/bin/python2 /home/pi/ros_catkin_ws/install_isolated/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/pi/ros_catkin_ws/src/ros_comm/roswtf --package=roswtf --results-filename test_roswtf.xml --results-base-dir \"/home/pi/ros_catkin_ws/build_isolated/roswtf/test_results\" /home/pi/ros_catkin_ws/src/ros_comm/roswtf/test/roswtf.test ")
set_tests_properties(_ctest_roswtf_rostest_test_roswtf.test PROPERTIES  _BACKTRACE_TRIPLES "/home/pi/ros_catkin_ws/install_isolated/share/catkin/cmake/test/tests.cmake;143;add_test;/home/pi/ros_catkin_ws/install_isolated/share/rostest/cmake/rostest-extras.cmake;52;catkin_run_tests_target;/home/pi/ros_catkin_ws/src/ros_comm/roswtf/CMakeLists.txt;9;add_rostest;/home/pi/ros_catkin_ws/src/ros_comm/roswtf/CMakeLists.txt;0;")
subdirs("gtest")
