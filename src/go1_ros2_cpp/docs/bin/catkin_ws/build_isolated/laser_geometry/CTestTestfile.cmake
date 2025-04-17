# CMake generated Testfile for 
# Source directory: /home/pi/catkin_ws/src/laser_geometry
# Build directory: /home/pi/catkin_ws/build_isolated/laser_geometry
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_laser_geometry_gtest_projection_test "/home/pi/catkin_ws/build_isolated/laser_geometry/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/pi/catkin_ws/build_isolated/laser_geometry/test_results/laser_geometry/gtest-projection_test.xml" "--return-code" "/home/pi/catkin_ws/devel_isolated/laser_geometry/lib/laser_geometry/projection_test --gtest_output=xml:/home/pi/catkin_ws/build_isolated/laser_geometry/test_results/laser_geometry/gtest-projection_test.xml")
set_tests_properties(_ctest_laser_geometry_gtest_projection_test PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/melodic/share/catkin/cmake/test/tests.cmake;143;add_test;/opt/ros/melodic/share/catkin/cmake/test/gtest.cmake;89;catkin_run_tests_target;/opt/ros/melodic/share/catkin/cmake/test/gtest.cmake;28;_catkin_add_google_test;/home/pi/catkin_ws/src/laser_geometry/CMakeLists.txt;37;catkin_add_gtest;/home/pi/catkin_ws/src/laser_geometry/CMakeLists.txt;0;")
subdirs("gtest")
