// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <utility>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::pair;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

void check_ans(const vector<int>& ratings, const vector<int>& C) {
  for (size_t i = 0; i < ratings.size(); ++i) {
    if (i > 0) {
      assert((ratings[i] > ratings[i - 1] && C[i] > C[i - 1]) ||
             (ratings[i] < ratings[i - 1] && C[i] < C[i - 1]) ||
             ratings[i] == ratings[i - 1]);
    }
    if (i + 1 < ratings.size()) {
      assert((ratings[i] > ratings[i + 1] && C[i] > C[i + 1]) ||
             (ratings[i] < ratings[i + 1] && C[i] < C[i + 1]) ||
             ratings[i] == ratings[i + 1]);
    }
  }
}

// @include
vector<int> calculate_bonus(const vector<int>& ratings) {
  // T stores the amount of bonus each one is assigned.
  vector<int> T(ratings.size(), 1);
  // From left to right.
  for (int i = 1; i < ratings.size(); ++i) {
    if (ratings[i] > ratings[i - 1]) {
      T[i] = T[i - 1] + 1;
    }
  }
  // From right to left.
  for (int i = ratings.size() - 2; i >= 0; --i) {
    if (ratings[i] > ratings[i + 1]) {
      T[i] = max(T[i], T[i + 1] + 1);
    }
  }
  return T;
}
// @exclude

template <typename T>
bool equal_vector(const vector<T>& A, const vector<T>& B) {
  return A.size() == B.size() && equal(A.begin(), A.end(), B.begin());
}

void small_test() {
  vector<int> A = {1, 2, 2};
  vector<int> golden_A = {1, 2, 1};
  assert(equal_vector(calculate_bonus(A), golden_A));
  A = {1,2,3,2,1};
  golden_A = {1, 2, 3, 2, 1};
  assert(equal_vector(calculate_bonus(A), golden_A));
}

int main(int argc, char* argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  for (int times = 0; times < 1000; ++times) {
    int n;
    if (argc == 2) {
      n = stoi(argv[1]);
    } else {
      uniform_int_distribution<int> dis(1, 1000);
      n = dis(gen);
    }
    vector<int> ratings;
    uniform_int_distribution<int> dis(1, 10000);
    for (int i = 0; i < n; ++i) {
      ratings.emplace_back(dis(gen));
    }
    auto T = calculate_bonus(ratings);
    check_ans(ratings, T);
  }
  return 0;
}
