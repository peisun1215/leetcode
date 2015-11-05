#include <cassert>
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

typedef long long int64;

class Solution {
public:
  vector<string> addOperators(string num, int target) {
    assert(!num.empty());
    return addOperators(num, target, "", 1);
  }

  vector<string> addOperators(const string& num,
			      int64 target,
			      string mul_expr,
			      int64 mul) {
    assert(!num.empty());

    vector<string> results;

    // Treat num as one number.
    std::cout << "aaa: " << num << endl;
    if (!isLeadingZeros(num) && stoi(num) * mul == target) {
      results.push_back(num + mul_expr);
    }

    // num[0:i+1), num[i + 1,).
    // When size = 1, this for loop is not excuted.
    for (int64 i = 0; i < num.size() - 1; ++i) {
      string left = num.substr(0, i + 1);
      string right = num.substr(i + 1);
      if (isLeadingZeros(right)) continue;

      int64 right_int64 = stol(right);

      // +.
      auto add_results = addOperators(left, target - right_int64 * mul, "", 1);
      for (const auto& j : add_results) {
	results.push_back(j + "+" + right + mul_expr);
      }

      // -.
      auto minus_results = addOperators(
	  left, target + right_int64 * mul, "", 1);
      for (const auto& j : minus_results) {
	results.push_back(j + "-" + right + mul_expr);
      }

      // *.
      auto mul_results = addOperators(
	  left, target, "*" + right + mul_expr, right_int64 * mul);
      for (const auto& j : mul_results) {
	results.push_back(j);
      }
    }

    return results;
  }

  bool isLeadingZeros(const string& s) {
    assert(!s.empty());

    return s.size() > 1 && s[0] == '0';
  }
};


int main(int argc, char** argv) {
  string num(argv[1]);
  int target = stoi(string(argv[2]));

  Solution s;
  for (auto &i : s.addOperators(num, target)) {
    std::cout << i << endl;
  }

  return 0;
}
