cmake_minimum_required(VERSION 2.8.3)
project(tensorflow_ros_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  tensorflow_ros_cpp
)

catkin_package()

include_directories(
  # needs to be first so that the tensorflow versions of includes are always treated first (not needed on all systems, but sometimes it is).
  ${tensorflow_ros_cpp_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

add_executable(tensorflow_ros_test_node src/test.cpp)
add_dependencies(tensorflow_ros_test_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
# again, tensorflow_ros_cpp_LIBRARIES need to go first in some setups
target_link_libraries(tensorflow_ros_test_node ${tensorflow_ros_cpp_LIBRARIES} ${catkin_LIBRARIES})

if(${CATKIN_ENABLE_TESTING})
  catkin_add_gtest(test_tensorflow_ros_cpp tests/unit_test.cpp)
  add_dependencies(test_tensorflow_ros_cpp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
  target_link_libraries(test_tensorflow_ros_cpp ${tensorflow_ros_cpp_LIBRARIES} ${catkin_LIBRARIES})
endif()
