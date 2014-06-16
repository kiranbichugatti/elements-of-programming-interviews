// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::min;
using std::ostream_iterator;
using std::pair;
using std::random_device;
using std::stack;
using std::stoi;
using std::uniform_int_distribution;
using std::vector;

// @include
int calculate_trapping_water(const vector<int>& A) {
  if (A.empty()) {
    return 0;
  }

  // Find the index with maximum height.
  int max_h = distance(A.cbegin(), max_element(A.cbegin(), A.cend()));

  // Calculate the water within [1 : max_h - 1].
  int sum = 0, left = A.front();
  for (int i = 1; i < max_h; ++i) {
    if (A[i] >= left) {
      left = A[i];
    } else {
      sum += left - A[i];
    }
  }

  // Calculate the water within [max_h + 1 : A.size() - 2].
  int right = A.back();
  for (int i = A.size() - 2; i > max_h; --i) {
    if (A[i] >= right) {
      right = A[i];
    } else {
      sum += right - A[i];
    }
  }
  return sum;
}
// @exclude

// Stack approach, O(n) time, O(n) space
int check_answer(const vector<int> &A) {
  stack<pair<int, int>> s;
  int sum = 0;
  for (size_t i = 0; i < A.size(); ++i) {
    while (!s.empty() && s.top().second <= A[i]) {
      int bottom = s.top().second;
      s.pop();
      if (s.empty()) {
        break;
      }
      int top = min(s.top().second, A[i]);
      sum += (top - bottom) * (i - s.top().first - 1);
    }
    s.emplace(i, A[i]);
  }
  return sum;
}

void small_test() {
  vector<int> A = {1, 0, 3, 2, 5, 0, 1};
  assert(calculate_trapping_water(A) == 3);
  A = {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1};
  cout << calculate_trapping_water(A) << endl;
  assert(calculate_trapping_water(A) == 1);
}

int main(int argc, char *argv[]) {
  small_test();
  default_random_engine gen((random_device())());
  for (int times = 0; times < 10000; ++times) {
    int n;
    if (argc == 2) {
      n = stoi(argv[1]);
    } else {
      uniform_int_distribution<int> n_dis(1, 1000);
      n = n_dis(gen);
    }
    vector<int> A;
    uniform_int_distribution<int> A_dis(0, 10);
    generate_n(back_inserter(A), n, [&] { return A_dis(gen); } );
    copy(A.cbegin(), A.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
    cout << check_answer(A) << " " << calculate_trapping_water(A) << endl;
    assert(check_answer(A) == calculate_trapping_water(A));
  }
  return 0;
}
