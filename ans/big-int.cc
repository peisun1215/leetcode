#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

using std::string;
using std::to_string;

class BigInt {
public:
  explicit BigInt(const string &s) : value_(s) {
    assert(!s.empty());
  };

  friend bool operator<=(const BigInt&left, const BigInt& right) {
    const string& l = left.value();
    const string& r = right.value();
    if (l.size() < r.size()) return true;
    if (l.size() > r.size()) return false;
    std::size_t i = 0;
    while (i < l.size() && l.at(i) == r.at(i)) {
      ++i;
    }
    if (i == l.size()) return true;
    return l.at(i) <= r.at(i);
  }

  // abs -.
  friend BigInt operator-(const BigInt& left, const BigInt& right) {
    return right <= left ? minus(left, right) : minus(right, left);
  }

  friend BigInt minus(const BigInt& left, const BigInt& right) {
    const string& l = left.value();
    const string& r = right.value();
    string result;
    int i = l.size() - 1;
    int j = r.size() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0) {
      int a = i >= 0 ? l.at(i) - '0' : 0;
      a -= carry;
      int b = j >= 0 ? r.at(j) - '0' : 0;
      int diff;
      if (a < b) {
        diff = 10 + a - b;
        carry = 1;
      } else {
        diff = a - b;
        carry = 0;
      }
      result += to_string(diff);
      --i; --j;
    }
    std::reverse(result.begin(), result.end());
    return BigInt(result);
  }

  friend BigInt operator+(const BigInt& left, const BigInt& right) {
    const string& l = left.value();
    const string& r = right.value();

    string result;
    int i = l.size() - 1;
    int j = r.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0) {
      int a = i >= 0 ? l.at(i) - '0' : 0;
      int b = j >= 0 ? r.at(j) - '0' : 0;
      int sum = (a + b + carry) % 10;
      carry = (a + b + carry) / 10;

      result += to_string(sum);
      --i;
      --j;
    }
    if (carry > 0) {
      result += to_string(carry);
    }
    std::reverse(result.begin(), result.end());

    return BigInt(result);
  }

  friend std::ostream& operator<<(std::ostream& out, const BigInt& bi) {
    return out << bi.value();
  }

  const string& value() const {
    return value_;
  }

private:
  const string value_;
};


int main(int argc, char** argv) {
  assert(argc == 3);

  std::cout << BigInt(argv[1]) + BigInt(argv[2]) << std::endl;
  std::cout << BigInt(argv[1]) - BigInt(argv[2]) << std::endl;
  return 0;
}
