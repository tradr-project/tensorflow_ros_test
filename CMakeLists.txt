cmake_minimum_required(VERSION 3.5)
project(tensorflow_ros_test)

if("$ENV{ROS_DISTRO}" STRLESS "kinetic")
    message(WARNING "Your system can probably run an easier-to-use version of this test. Switch to master branch.")
endif()

# Since ROS Kinetic/Ubuntu Xenial, there is a version clash between the C++ ABI used to compile ROS (C++11)
# and TF (C++03) which makes it impossible to mix ROS and TF code in a single file.
# However, if the TF code is separated to its own library which is then linked to the ROS node,
# you can get the best of both worlds (given some limitations to the API of your library).
# Read comments in the example files to learn about these limitations.
# See also https://github.com/tradr-project/tensorflow_ros#c-abi-difference-problems .

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
)

# call find_package separately so that tensorflow isn't included in everything
find_package(tensorflow_ros_cpp REQUIRED)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# Build the TF library. Do NOT include catkin_LIBRARIES/catkin_INCLUDE_DIRS here!
add_library(tensorflow_ros_test_lib src/lib.cpp)
add_dependencies(tensorflow_ros_test_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(tensorflow_ros_test_lib BEFORE PRIVATE ${tensorflow_ros_cpp_INCLUDE_DIRS})
target_link_libraries(tensorflow_ros_test_lib ${tensorflow_ros_cpp_LIBRARIES})
# Compile the TF library using CXX03 ABI.
target_compile_definitions(tensorflow_ros_test_lib PRIVATE -D_GLIBCXX_USE_CXX11_ABI=0)

# Build the ROS node and link the TF library to it. Do NOT include tensorflow_ros_LIBRARIES here!
add_executable(tensorflow_ros_test_node src/test.cpp)
add_dependencies(tensorflow_ros_test_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(tensorflow_ros_test_node tensorflow_ros_test_lib ${catkin_LIBRARIES})

if(${CATKIN_ENABLE_TESTING})
  catkin_add_gtest(test_tensorflow_ros tests/unit_test.cpp)
  add_dependencies(test_tensorflow_ros ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
  target_link_libraries(test_tensorflow_ros tensorflow_ros_test_lib ${catkin_LIBRARIES})
endif()
