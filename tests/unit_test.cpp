#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"

#include <ros/package.h>

#include <gtest/gtest.h>


using namespace tensorflow;

class TestTensorflowRosFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
      // Initialize a tensorflow session
      Status status = NewSession(SessionOptions(), &this->session);
      ASSERT_TRUE(status.ok());
    }

    virtual void TearDown() {
      this->session->Close();
    }

    Session* session;

};

TEST_F(TestTensorflowRosFixture, TestSessionRun) {
  // Read in the protobuf graph we exported.
  // See https://stackoverflow.com/a/43639305/1076564 for other ways of saving and restoring Tensorflow graphs.
  GraphDef graph_def;
  Status status = ReadBinaryProto(Env::Default(), ros::package::getPath("tensorflow_ros_test") + "/models/train.pb", &graph_def);
  ASSERT_TRUE(status.ok());

  // Add the graph to the session
  status = session->Create(graph_def);
  ASSERT_TRUE(status.ok());

  // Setup inputs and outputs:

  // Our graph doesn't require any inputs, since it specifies default values,
  // but we'll change an input to demonstrate.
  Tensor a(DT_FLOAT, TensorShape());
  a.scalar<float>()() = 3.0;

  Tensor b(DT_FLOAT, TensorShape());
  b.scalar<float>()() = 2.0;

  std::vector<std::pair<string, tensorflow::Tensor>> inputs = {
    { "a", a },
    { "b", b },
  };

  // The session will initialize the outputs
  std::vector<tensorflow::Tensor> outputs;

  // Run the session, evaluating our "c" operation from the graph
  status = this->session->Run(inputs, {"c"}, {}, &outputs);
  ASSERT_TRUE(status.ok());

  // Grab the first output (we only evaluated one graph node: "c")
  // and convert the node to a scalar representation.
  auto output_c = outputs[0].scalar<float>();

  EXPECT_EQ(6, static_cast<float>(output_c(0)));
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}