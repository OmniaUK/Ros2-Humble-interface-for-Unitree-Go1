##
# Based on tutlesim launch from: https://docs.ros.org/en/humble/Tutorials/Intermediate/Launch/Creating-Launch-Files.html#write-the-launch-file
# Later modified to work for go1_ros2_cpp package.
#
# Unitree Go1 Ros wrapper launcher for control
# 
import os

from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.actions import Node, PushRosNamespace

def generate_launch_description():
    # Robot namespace
    namespace = 'go1_0000'
    
    legged_sdk_node = Node(
        package='go1_ros2_cpp',
        executable='legged_controller',
        name='legged_controller',
    )
    
    face_light_sdk_node = Node(
        package='go1_ros2_cpp',
        executable='face_light_controller',
        name='face_light_controller',
    )
    
    # Template for additional nodes
    # additional_node = Node(
    #     package='go1_ros2_cpp',
    #     executable='_controller',
    #     name='_controller',
    #     namespace=namespace
    # )
    
    return LaunchDescription([
        PushRosNamespace(namespace),
        legged_sdk_node,
        face_light_sdk_node,
    ])


