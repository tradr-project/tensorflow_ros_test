#include <cstdlib>

#include <ros/package.h>

#include <gtest/gtest.h>

#include "tensorflow_ros_test/lib.h"

TEST(TestTensorflowRosFixture, testSessionRun) {

  const char* env_model_path = std::getenv("TENSORFLOW_ROS_MODEL_PATH");
  const std::string model_path = (env_model_path ? env_model_path : ros::package::getPath("tensorflow_ros_test") + "/models/train.pb");

  float result = 0;

  int status = do_tensorflow(model_path.c_str(), &result);

  EXPECT_EQ(0, status);
  EXPECT_EQ(6, result);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
