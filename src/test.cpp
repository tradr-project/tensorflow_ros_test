#include <ros/ros.h>
#include <ros/package.h>

#include "tensorflow_ros_test/lib.h"

// IMPORTANT: Do not include any Tensorflow headers here. All TF work has to be done in the
// linked library.

int main(int argc, char* argv[]) {
  ros::init(argc, argv, "tensorflow_test_with_ros");

  std::string model_path = ros::package::getPath("tensorflow_ros_test") + "/models/train.pb";

  // Call the library that does TF computations.
  return do_tensorflow(model_path.c_str());
}
