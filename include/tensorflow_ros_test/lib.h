#ifndef TENSORFLOW_ROS_TEST_LIB_H
#define TENSORFLOW_ROS_TEST_LIB_H

// IMPORTANT: Do not expose any tensorflow includes here - they could not be resolved by
// the code linking to this library. If you need e.g. class members of some TF type, use
// the PIMPL paradigm to hide them.

// IMPORTANT: Do not include anything from ROS here.

// IMPORTANT: It is better to use just primitive data types in this API of your library,
// since otherwise you might run into C++ ABI incompatibilities resulting in memory corruption.
// It is even better not to use std::string, but instead pass char* and convert it to std::string
// in the .cpp file. std::vector and std::list can also cause problems.

int do_tensorflow();

#endif //TENSORFLOW_ROS_TEST_LIB_H
