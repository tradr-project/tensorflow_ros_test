# tensorflow\_ros\_test

A package for testing if [tensorflow\_ros](https://github.com/tradr-project/tensorflow_ros) works on your machine.

If you succeed to build it, try running

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

Specifically, if you get linking errors containing `cxx11` words,
it means your system is too new to use the pip-installed Tensorflow
easily. Consult [https://github.com/tradr-project/tensorflow_ros#c-abi-difference-problems].
One solution is to hide all Tensorflow code
[behind a C API as shown here](https://github.com/tradr-project/tensorflow_ros_test/tree/kinetic-devel).
