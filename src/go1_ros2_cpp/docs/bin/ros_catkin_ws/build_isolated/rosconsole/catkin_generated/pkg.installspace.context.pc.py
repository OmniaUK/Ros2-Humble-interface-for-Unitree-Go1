# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/usr/include".split(';') if "${prefix}/include;/usr/include" != "" else []
PROJECT_CATKIN_DEPENDS = "cpp_common;rostime".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lrosconsole;-lrosconsole_log4cxx;-lrosconsole_backend_interface;/usr/lib/aarch64-linux-gnu/liblog4cxx.so;/usr/lib/aarch64-linux-gnu/libboost_regex.so;/usr/lib/aarch64-linux-gnu/libboost_system.so;/usr/lib/aarch64-linux-gnu/libboost_thread.so;-pthread;/usr/lib/aarch64-linux-gnu/libboost_chrono.so;/usr/lib/aarch64-linux-gnu/libboost_date_time.so;/usr/lib/aarch64-linux-gnu/libboost_atomic.so".split(';') if "-lrosconsole;-lrosconsole_log4cxx;-lrosconsole_backend_interface;/usr/lib/aarch64-linux-gnu/liblog4cxx.so;/usr/lib/aarch64-linux-gnu/libboost_regex.so;/usr/lib/aarch64-linux-gnu/libboost_system.so;/usr/lib/aarch64-linux-gnu/libboost_thread.so;-pthread;/usr/lib/aarch64-linux-gnu/libboost_chrono.so;/usr/lib/aarch64-linux-gnu/libboost_date_time.so;/usr/lib/aarch64-linux-gnu/libboost_atomic.so" != "" else []
PROJECT_NAME = "rosconsole"
PROJECT_SPACE_DIR = "/opt/ros/melodic"
PROJECT_VERSION = "1.13.11"
