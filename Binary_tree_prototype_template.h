// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BINARY_TREE_PROTOTYPE_TEMPLATE_H_
#define SOLUTIONS_BINARY_TREE_PROTOTYPE_TEMPLATE_H_

#include <memory>

using std::shared_ptr;

// @include
template <typename T>
struct BinaryTree {
  T data;
  shared_ptr<BinaryTree<T>> left, right;
};
// @exclude
#endif  // SOLUTIONS_BINARY_TREE_PROTOTYPE_TEMPLATE_H_
