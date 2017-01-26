cmake_minimum_required(VERSION 2.8.3)
project(tensorflow_ros_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tensorflow_ros
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(tensorflow_ros_test_node src/test.cpp)
add_dependencies(tensorflow_ros_test_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(tensorflow_ros_test_node ${catkin_LIBRARIES})
