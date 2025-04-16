# -*- coding: utf-8 -*-
from __future__ import print_function

import os
import stat
import sys

# find the import for catkin's python package - either from source space or from an installed underlay
if os.path.exists(os.path.join('/opt/ros/melodic/share/catkin/cmake', 'catkinConfig.cmake.in')):
    sys.path.insert(0, os.path.join('/opt/ros/melodic/share/catkin/cmake', '..', 'python'))
try:
    from catkin.environment_cache import generate_environment_script
except ImportError:
    # search for catkin package in all workspaces and prepend to path
    for workspace in '/home/pi/catkin_ws/devel_isolated/visualization_msgs;/home/pi/catkin_ws/devel_isolated/robot_state_publisher;/home/pi/catkin_ws/devel_isolated/kdl_parser;/home/pi/catkin_ws/devel_isolated/urdf;/home/pi/catkin_ws/devel_isolated/urdf_parser_plugin;/home/pi/catkin_ws/devel_isolated/resource_retriever;/home/pi/catkin_ws/devel_isolated/python_qt_binding;/home/pi/catkin_ws/devel_isolated/map_msgs;/home/pi/catkin_ws/devel_isolated/laser_geometry;/home/pi/catkin_ws/devel_isolated/image_transport;/opt/ros/melodic'.split(';'):
        python_path = os.path.join(workspace, 'lib/python2.7/dist-packages')
        if os.path.isdir(os.path.join(python_path, 'catkin')):
            sys.path.insert(0, python_path)
            break
    from catkin.environment_cache import generate_environment_script

code = generate_environment_script('/home/pi/catkin_ws/devel_isolated/interactive_markers/env.sh')

output_filename = '/home/pi/catkin_ws/build_isolated/interactive_markers/catkin_generated/setup_cached.sh'
with open(output_filename, 'w') as f:
    # print('Generate script for cached setup "%s"' % output_filename)
    f.write('\n'.join(code))

mode = os.stat(output_filename).st_mode
os.chmod(output_filename, mode | stat.S_IXUSR)
