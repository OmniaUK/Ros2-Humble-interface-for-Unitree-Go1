# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/usr/include".split(';') if "${prefix}/include;/usr/include" != "" else []
PROJECT_CATKIN_DEPENDS = "pluginlib;roslz4".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lrosbag_storage;/usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4;/usr/lib/aarch64-linux-gnu/libboost_date_time.so;/usr/lib/aarch64-linux-gnu/libboost_filesystem.so;/usr/lib/aarch64-linux-gnu/libboost_program_options.so;/usr/lib/aarch64-linux-gnu/libboost_regex.so;/usr/lib/aarch64-linux-gnu/libboost_system.so".split(';') if "-lrosbag_storage;/usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4;/usr/lib/aarch64-linux-gnu/libboost_date_time.so;/usr/lib/aarch64-linux-gnu/libboost_filesystem.so;/usr/lib/aarch64-linux-gnu/libboost_program_options.so;/usr/lib/aarch64-linux-gnu/libboost_regex.so;/usr/lib/aarch64-linux-gnu/libboost_system.so" != "" else []
PROJECT_NAME = "rosbag_storage"
PROJECT_SPACE_DIR = "/opt/ros/melodic"
PROJECT_VERSION = "1.14.5"
