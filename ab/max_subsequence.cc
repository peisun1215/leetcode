// [4,9,6]=10
// [4,10,3,1,5]=15

// 10:21PM - 10:41PM.

// Algorithm:
// D[i]: max subarrary sum for [0, i].
// B[i]: whether A[i] is included in D[i].

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

int64 MaxNonConsecutiveSubSeqSum(const vector<int64>& inputs) {
  assert(!inputs.empty());

  vector<int64> results(inputs.size(), 0);
  vector<bool> included(inputs.size(), false);
  if (inputs[0] > 0) {
    results[0] = inputs.at(0);
    included[0] = true;
  }

  for (int64 i = 1; i < static_cast<int64>(inputs.size()); ++i) {
    if (inputs.at(i) <= 0) {
      results[i] = results[i - 1];
    } else if (!included[i - 1]) {
      results[i] = results[i - 1] + inputs.at(i);
      included[i] = true;
    } else {
      if (i > 1) {
        results[i] = results[i - 2] + inputs.at(i);
      } else {
        results[i] = inputs.at(i);
      }
      if (results[i] > results[i - 1]) {
        included[i] = true;
      } else {
        results[i] = results[i - 1];
        included[i] = included[i - 1];
      }
    }
  }

  return results[inputs.size() - 1];
}

int main(int argc, char** argv) {
  vector<int64> inputs = {4, 10, 3, -1, 3};

  auto res = MaxNonConsecutiveSubSeqSum(inputs);

  cout << res << endl;

  return 0;
}

