cmake_minimum_required(VERSION 2.8.3)
project(tensorflow_ros_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tensorflow_ros
)

catkin_package()

include_directories(
  # needs to be first so that the tensorflow versions of includes are always treated first (not needed on all systems, but sometimes it is).
  ${tensorflow_ros_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

add_executable(tensorflow_ros_test_node src/test.cpp)
add_dependencies(tensorflow_ros_test_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# again, tensorflow_ros_LIBRARIES need to go first in some setups
target_link_libraries(tensorflow_ros_test_node ${tensorflow_ros_LIBRARIES} ${catkin_LIBRARIES})
