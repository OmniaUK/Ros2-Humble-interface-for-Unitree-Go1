# This test file was created to test the ROS2 node environments are running correctly.
# Code written in this file was written while following a youtube tutorial: https://www.youtube.com/watch?v=h-1IhC01T1c

# general imports
import unittest
import time
# Ros imports
import launch
import launch_ros
import launch_ros.actions
import launch_testing.actions
import rclpy
from std_msgs.msg import Float32
from go1_ros2_cpp.msg import HighState
from go1_ros2_cpp.msg import LED



print("Starting the test enviroment...")


# Launch description to start the legged_controller and face_light_controller nodes
# starting the ROS2 environment for tests.
def generate_test_description():
    logger = launch.substitutions.LaunchConfiguration("log_level")

    log_argument = launch.actions.DeclareLaunchArgument(
        "log_level",
        default_value=["warn"],
        description="Logging level"
    )
    
    # legged_controller
    leggedsdk_node = launch_ros.actions.Node(
        package="go1_ros2_cpp",
        executable="legged_controller",
        additional_env={"PYTHONBUFFERED": "1"},
        parameters=[{
            "simulated": True
        }],
        arguments=['--ros-args', '--log-level', logger]
    )
    
    # face_light_controller
    face_light_node = launch_ros.actions.Node(
        package="go1_ros2_cpp",
        executable="face_light_controller",
        additional_env={"PYTHONBUFFERED": "1"},
        parameters=[{
            "simulated": True
        }],
        arguments=['--ros-args', '--log-level', logger]
    )
    
    return (
        launch.LaunchDescription([
            log_argument,
            leggedsdk_node,
            face_light_node,
            launch_testing.actions.ReadyToTest(),
        ]),
        {
            'legged_controller': leggedsdk_node,
            'face_light_controller': face_light_node,
        }
    )


print("Starting the tests...")

class TestLeggedController(unittest.TestCase):
    
    @classmethod
    def setUpClass(cls):
        # Initialize the ROS2 context
        rclpy.init()
    
    @classmethod
    def tearDownClass(cls):
        # Shutdown the ROS2 context
        rclpy.shutdown()
        
    def setUp(self):
        self.node = rclpy.create_node("test_legged_controller")
        
    def tearDown(self):
        self.node.destroy_node()
        
    def test_legged_controller(self, legged_controller, proc_output):
        msgs_rx = []
        
        mode_status_subscriber = self.node.create_subscription(
            HighState,
            "legged_data/status/mode",
            lambda msg: msgs_rx.append(msg),
            10
        )
        
        # Check if messages are being received
        try:
            end_time = time.time() + 10 # 10 seconds timeout
            while time.time() < end_time:
                rclpy.spin_once(self.node, timeout_sec=0.1) # wait for the message to be published
                if len(msgs_rx) > 2:
                    break
            msg = msgs_rx[0]
            self.assertGreater(len(msgs_rx), 2, "Messages not publishing")
            self.assertEqual(msg.mode, 0, f"Expected mode=0 but got {msg.mode}") # Check if the message is being published with the correct data format
            
            
            
        finally:
            self.node.destroy_subscription(mode_status_subscriber)
            
    
    def test_face_light_controller(self, face_light_controller, proc_output):
        msgs_rx = []
        
     
        
        face_light_subscriber = self.node.create_subscription(
            LED,
            "face/led",  # Update with actual topic name
            lambda msg: msgs_rx.append(msg),
            10
        )
        
        # Create a publisher to send LED messages
        face_light_test_data_publisher = self.node.create_publisher(
            LED,
            "face/led",
            10
        )
        
        msg = LED()
        # Set random values for LED message
        msg.r = 255
        msg.g = 200
        msg.b = 155
        msg.id = 5
        
        # Check if the message data is being published correctly
        try:
            end_time = time.time() + 10 # 10 seconds timeout
            while time.time() < end_time:
                face_light_test_data_publisher.publish(msg)
                rclpy.spin_once(self.node, timeout_sec=0.1) # wait for the message to be published
                if len(msgs_rx) > 2:
                    break
            
            self.assertGreater(len(msgs_rx), 0, "Messages not publishing")
            msg = msgs_rx[0]
            assert msg.r == 255, f"Expected r=255 but got {msg.r}"
            assert msg.g == 200, f"Expected g=200 but got {msg.g}"
            assert msg.b == 155, f"Expected b=155 but got {msg.b}"
            assert msg.id == 5, f"Expected id=5 but got {msg.id}"
                
        finally:
            self.node.destroy_publisher(face_light_test_data_publisher)
            self.node.destroy_subscription(face_light_subscriber)
        
        
print("Tests finished.")
print("Shutting down the test environment...")