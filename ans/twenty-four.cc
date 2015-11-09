#include <iostream>
#include <vector>
#include <string>
#include <cassert>

typedef long long int64;
using namespace std;

namespace {
const int64 K = 24;

struct D {
  double num = 0;
  string expr;
  D(double _num, const string& _expr) : num(_num), expr(_expr) {};
};

bool TwentyFour(const vector<D>& nums, vector<string>& result);
vector<D> Expand(const D& a, const D& b);

vector<string> TwentyFour(const string& nums) {
  int i = 0;
  vector<D> nums_copy;
  while (i < nums.size()) {
    int j = nums.find_first_of(",", i);
    j = j == string::npos ? nums.size() : j;
    nums_copy.emplace_back(stoi(nums.substr(i, j - i)), nums.substr(i, j - i));
    std::cout << nums.substr(i,  j - i) << endl;
    i = j + 1;
  }

  vector<string> result;
  TwentyFour(nums_copy, result);
  return result;
}

bool TwentyFour(const vector<D>& nums, vector<string>& result) {
  if (nums.empty()) return false;
  if (nums.size() == 1 && nums.front().num == K) {
    result.push_back(nums.front().expr);
    return true;
  } else if (nums.size() == 1) {
    return false;
  }

  // Pick two front nums.
  for (int i = 0; i < nums.size() - 1; ++i) {
    for (int j = i + 1; j < nums.size(); ++j) {
      vector<D> nums_copy;
      for (int k = 0; k < nums.size(); ++k) {
        if (k == i || k == j) continue;
        nums_copy.push_back(nums.at(k));
      }
      vector<D> nexts = Expand(nums.at(i), nums.at(j));
      for (auto& next : nexts) {
        nums_copy.push_back(next);
        if (TwentyFour(nums_copy, result)) return true;
        nums_copy.pop_back();
      }
    }
  }
  return false;
}

vector<D> Expand(const D& a, const D& b) {
  vector<D> result;
  result.emplace_back(1.0 *a.num + b.num, "(" + a.expr + " + " + b.expr + ")");
  result.emplace_back(1.0*a.num * b.num, "(" + a.expr + " * " + b.expr + ")");
  result.emplace_back(1.0*a.num - b.num, "(" + a.expr + " - " + b.expr + ")");
  result.emplace_back(1.0*b.num - a.num, "(" + b.expr + " - " + a.expr + ")");
  if (b.num != 0) {
    result.emplace_back(1.0*a.num / b.num, "(" + a.expr + " / " + b.expr + ")");
  }
  if (a.num != 0) {
    result.emplace_back(1.0* b.num / a.num, "(" + b.expr + " / " + a.expr + ")");
  }
  return result;
}
}

int main(int argc, char** argv) {
  auto r = TwentyFour(string(argv[1]));
  for (auto i : r) {
    std::cout << i << std::endl;
  }
}
