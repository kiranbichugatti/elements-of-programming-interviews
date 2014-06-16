// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ostream_iterator;
using std::random_device;
using std::stoul;
using std::uniform_int_distribution;
using std::vector;

void subsets_unique_helper(const vector<int>& A, size_t start, vector<int>* ans, vector<vector<int>>* res);

// @include
vector<vector<int>> subsets_unique(vector<int> A) {
  vector<vector<int>> res;
  vector<int> ans;

  sort(A.begin(), A.end());
  subsets_unique_helper(A, 0, &ans, &res);
  return res;
}

void subsets_unique_helper(const vector<int>& A, size_t start, vector<int>* ans, vector<vector<int>>* res) {
  res->emplace_back(*ans);
  for (size_t i = start; i < A.size(); ++i) {
    if (i != start && A[i - 1] == A[i]) {
      continue;
    }
    ans->emplace_back(A[i]);
    subsets_unique_helper(A, i + 1, ans, res);
    ans->pop_back();
  }
}
// @exclude

int main(int argc, char** argv) {
  default_random_engine gen((random_device())());
  size_t n;
  if (argc == 2) {
    n = stoul(argv[1]);
  } else {
    uniform_int_distribution<size_t> dis(1, 5);
    n = dis(gen);
  }
  // Creates A with duplicate elements.
  vector<int> A;
  for (size_t i = 0; i < (n << 1); ++i) {
    A.emplace_back(static_cast<int>(i)), A.emplace_back(static_cast<int>(i));
  }
  cout << "n = " << n << endl;
  A.clear();
  A = { 1, 2, 3, 4, 5, 6, 7, 8, 10, 0 };
  auto res = subsets_unique(A);
  for (const auto& vec : res) {
    copy(vec.cbegin(), vec.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
  }
  return 0;
}
