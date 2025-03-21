# Ros2-Humble-interface-for-Unitree-Go1

Version 0.1 - Private Alpha

# About
This is a ROS2 Wraper package designed to replace the developer api from the (no longer developed or supported):
- Unitree_Legged_SDK
- UnitreecameraSDK
- faceLightSDK
With some additional features added to allow for better software control over the robot.

The goal of this software, as part of my University Major-Project, was to create a more standardized development API for use of the Unitree Go1 hardware.
My hopes were to aid my University to use the robot for research use, but also allow those with the same hardware to have open-source access to a better option (with comprehensive documentation) that would allow for faster development using a familiar ROS2 Humble framework.

With special thanks to:
- Patricia Shaw
- Tomos Fearn
- Helen Miles
- Aberystwyth University

# Dependencies
- Ros2 Humble (desktop full) (Ubuntu 22.04 Reccomended)
```
https://docs.ros.org/en/humble/Installation.html
```
- Rviz2
```
https://docs.ros.org/en/humble/Tutorials/Intermediate/RViz/RViz-User-Guide/RViz-User-Guide.html#install-or-build-rviz
```
- Boost (Version 16.5, newer versions seem to build with errors or break stuff with UnitreeLeggedSDK)

```
Boost install instructions:

Step 1:
https://www.boost.org/users/history/version_1_65_0.html
-- Download: boost_1_65_0.tar.gz

Step 2:
Open terminal and run:
cd Downloads/
tar -xzf boost_1_65_0.tar.gz 

Step 3:
Once unpackaged:
cd boost_1_65_0/

Step 4:
./bootstrap.sh

Step 5:
sudo ./b2

Step 6:
sudo ./b2 install
```
# How to install
To Do...

# Known issues
~ Package on builds on Intel systems - This is due to the hardcode for arm64 use. CMake wont allow me to use variables apparently...
~ 
