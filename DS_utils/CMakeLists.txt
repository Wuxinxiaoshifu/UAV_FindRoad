
cmake_minimum_required(VERSION 2.8.3)
project(ds_utils)
 
 
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  tf
)
 
 
catkin_package(
 
)
 
 
## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
 
 
add_executable(tf2odom src/tf2odom.cpp)
target_link_libraries(tf2odom ${catkin_LIBRARIES})
