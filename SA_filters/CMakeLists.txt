cmake_minimum_required(VERSION 3.0.2)
project(SA_filters)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  image_transport
  sensor_msgs
  geometry_msgs
  cv_bridge  
  #pluginlib
  #nodelet
)

find_package( OpenCV REQUIRED )
###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES SA_filters
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

#add executable and link both opencv and catkin libraries
add_executable( SA_filters src/Nav_Mode1.cpp ) #change the file here
target_link_libraries(SA_filters ${catkin_LIBRARIES})
target_link_libraries( SA_filters ${OpenCV_LIBRARIES} )  