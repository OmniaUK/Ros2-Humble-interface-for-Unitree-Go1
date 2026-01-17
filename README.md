# Ros2-Humble-interface-for-Unitree-Go1

Version 0.1 - Public (Early Access) Alpha.
Disclaimer - This project is still in progress and has many things I want to fix / change. It is however functional for the legged SDK

# About
This is a ROS2 Wraper package designed to replace the developer api from the (no longer developed or supported):
- Unitree_Legged_SDK -  Working
- UnitreecameraSDK - Use a ros2 Bridge
- faceLightSDK - Working
With some additional features added to allow for better software control over the robot.

The goal of this software, as part of my University Major-Project, was to create a more standardized development API for use of the Unitree Go1 hardware.
My hopes were to aid my University to use the robot for research, but also allow those with the same hardware in industry/ at home, to have open-source access to a better option (with comprehensive documentation) that would allow for faster development using a familiar ROS2 Humble framework.

With special thanks to:
- Dr. Patricia Shaw
- Dr. Tomos Fearn
- Dr. Helen Miles
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

- OpenCV2
```
pip install opencv-python
```
- udev
```
# In terminal:
sudo apt update
sudo apt install libudev-dev
```
# How to install
- Install the package to your home directory.

- Ensure all dependencies are installed

- In the terminal navigate to the head directory
```
cd ~/Ros2-Humble-interface-for-Unitree-Go1
```
- Build the package
```
Colcon Build
```

- Source bash.rc
```
source install/setup.bash
```

- Connect to the Go1 wireless network

- Run the package launch file
```
ros2 launch go1_ros2_cpp go1.launch.py
```



# Known issues
~ Package only builds on Intel systems - This is due to the hardcode for arm64 use. CMake wont allow me to use variables apparently...
~ 
