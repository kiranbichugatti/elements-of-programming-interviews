// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#include "./Binary_tree_prototype.h"
#include "./Binary_tree_utils.h"

using std::cout;
using std::endl;
using std::equal;
using std::stack;
using std::unique_ptr;
using std::vector;

// @include
vector<int> preorder_traversal(const unique_ptr<BinaryTreeNode<int>>& root) {
  if (!root) {
    return {};
  }

  stack<BinaryTreeNode<int>*> s;
  s.emplace(root.get());
  vector<int> res;
  while (!s.empty()) {
    auto curr = s.top();
    s.pop();
    res.emplace_back(curr->data);
    if (curr->right) {
      s.emplace(curr->right.get());
    }
    if (curr->left) {
      s.emplace(curr->left.get());
    }
  }
  return res;
}
// @exclude

int main(int argc, char** argv) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> root =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{3, nullptr, nullptr});
  root->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{2, nullptr, nullptr});
  root->left->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{1, nullptr, nullptr});
  root->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{5, nullptr, nullptr});
  root->right->left =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{4, nullptr, nullptr});
  root->right->right =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>{6, nullptr, nullptr});
  auto res = preorder_traversal(root), golden_res = generate_preorder(root);
  assert(res.size() == golden_res.size() &&
         equal(res.cbegin(), res.cend(), golden_res.cbegin()));
  return 0;
}
