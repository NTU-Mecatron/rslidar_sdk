from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution

def generate_launch_description():

    config_dir = PathJoinSubstitution([FindPackageShare("rslidar_sdk"), "config"])
    config_file = PathJoinSubstitution([config_dir, 'rslidar.param.yaml'])
    
    return LaunchDescription([
        Node(namespace='rslidar_sdk', package='rslidar_sdk', executable='rslidar_component_node', output='screen', parameters=[{'config_path': config_file}])
    ])
