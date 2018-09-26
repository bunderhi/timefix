cmake_minimum_required(VERSION 2.8.3)
project(nodelet_timefix)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  nodelet
  roscpp
  sensor_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

catkin_package(
   LIBRARIES nodelet_timefix
   CATKIN_DEPENDS nodelet roscpp rospy sensor_msgs
)


add_library(nodelet_timefix
   src/timefix.cpp
)

target_link_libraries(nodelet_timefix ${catkin_LIBRARIES})

if(catkin_EXPORTED_LIBRARIES)
  add_dependencies(nodelet_timefix ${catkin_EXPORTED_LIBRARIES})
endif()

## Mark the nodelet library for installations
install(TARGETS nodelet_timefix
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES nodelet_timefix.xml timefix.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
