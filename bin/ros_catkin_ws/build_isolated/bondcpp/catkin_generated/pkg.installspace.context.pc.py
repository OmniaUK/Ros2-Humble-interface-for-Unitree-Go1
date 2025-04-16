# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/usr/include".split(';') if "${prefix}/include;/usr/include" != "" else []
PROJECT_CATKIN_DEPENDS = "bond;roscpp;smclib".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lbondcpp".split(';') if "-lbondcpp" != "" else []
PROJECT_NAME = "bondcpp"
PROJECT_SPACE_DIR = "/opt/ros/melodic"
PROJECT_VERSION = "1.8.3"
