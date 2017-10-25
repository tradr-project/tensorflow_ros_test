#include <ros/ros.h>

#include "tensorflow_ros_test/lib.h"

// IMPORTANT: Do not include any Tensorflow headers here. All TF work has to be done in the
// linked library.

int main(int argc, char* argv[]) {
  ros::init(argc, argv, "tensorflow_test_with_ros");

  // Call the library that does TF computations.
  return do_tensorflow();
}
