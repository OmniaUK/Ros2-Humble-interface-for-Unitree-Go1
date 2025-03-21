##
# Based on tutlesim launch from: https://docs.ros.org/en/humble/Tutorials/Intermediate/Launch/Creating-Launch-Files.html#write-the-launch-file
# Later modified to work for go1_ros2_cpp package.
# 
import os

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='go1_ros2_cpp',
            namespace='Go1_0000',
            executable='legged_udp_rx',
            name='sim'
        ),
        Node(
            package='turtlesim',
            namespace='turtlesim2',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='turtlesim',
            executable='mimic',
            name='mimic',
            remappings=[
                ('/input/pose', '/turtlesim1/turtle1/pose'),
                ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
            ]
        )
    ])
