# tensorflow\_ros\_test

A package for testing if [tensorflow\_ros](https://github.com/tradr-project/tensorflow_ros) works on your machine.

**This branch contains a workaround for systems with clashing C++ ABIs. Don't use it unless you have to. First, start with the [master branch](https://github.com/tradr-project/tensorflow_ros_test) and test if it works for you.**

If you succeed to build tensorflow\_ros, try running

    rosrun tensorflow_ros_test tensorflow_ros_test_node

It tests running `models/train.pb` with a pre-built tensorflow graph.

You can create such a graph e.g. by:

    import tensorflow as tf
    import numpy as np

    with tf.Session() as sess:
        a = tf.Variable(5.0, name='a')
        b = tf.Variable(6.0, name='b')
        c = tf.multiply(a, b, name="c")

        sess.run(tf.initialize_all_variables())

        print a.eval() # 5.0
        print b.eval() # 6.0
        print c.eval() # 30.0

        tf.train.write_graph(sess.graph_def, 'models/', 'train.pb', as_text=False)

Thanks to [Jim Fleming](https://medium.com/jim-fleming/loading-a-tensorflow-graph-with-the-c-api-4caaff88463f#.x0ig91dd1) for the sample code.

## Troubleshooting

If you run into any kind of compilation/linking errors, be sure to read
[tensorflow\_ros README](https://github.com/tradr-project/tensorflow_ros)
as there are many information about which combination of Tensorflow
installation and system work together.