#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// Input: A = [x1, x2, ..., xn].1point3acres缃�
// Sum T = Round(x1+x2+... +xn)  ;  178.93E => 179
// Output: B = [y1, y2, ...., yn]
// Constraint #1: y1+y2+...+yn = T
// Constraint #2: minimize sum(abs(diff(xi - yi))).

typedef long long int64;

vector<int64> Round(const vector<double>& inputs) {
  const int64 sum_d =
    static_cast<int64>(std::accumulate(inputs.begin(),
                                       inputs.end(), 0.0) + 0.5);
  int64 sum_i = 0;
  vector<std::pair<double, std::size_t>> fractionals(inputs.size());
  vector<int64> integers(inputs.size(), 0);

  for (std::size_t i = 0; i < inputs.size(); ++i) {
    integers[i] = static_cast<int64>(inputs.at(i));
    sum_i += integers[i];
    fractionals[i] = make_pair(inputs.at(i) - integers[i], i);
  }

  assert(sum_i <= sum_d);
  if (sum_i == sum_d) return integers;

  // if the difference between sum_i and sum_d is small, use a heap.
  // But generally, we can sort.
  std::sort(fractionals.begin(), fractionals.end(),
            [](const std::pair<double, std::size_t>& x,
               const std::pair<double, std::size_t>& y)->bool {
              return x.first > y.first;
            });
  assert(sum_d - sum_i < static_cast<int64>(inputs.size()));
  for (int64 i = 0; i < sum_d - sum_i; ++i) {
    integers[fractionals[i].second]++;
  }

  return integers;
}

int main(int argc, char** argv) {
  vector<double> inputs = {1.2, 2.3, 3.4, 1.4, 0.1, 0.9, 1.5};

  vector<int64> outputs = Round(inputs);

  for (const auto i : inputs) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  for (auto i : outputs) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
