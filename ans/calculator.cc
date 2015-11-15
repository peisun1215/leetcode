#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Calculator {
public:
  //  class Element;
  Calculator() {}

  string RPN(const string& pn) {
    vector<Element> elements = ConvertToRPN(Parse(pn));
    string result;
    for (auto& e : elements) {
      result += " " + e.ToString();
    }
    return result;
  }

  double Eval(const string& pn) {
    vector<Element> elements = ConvertToRPN(Parse(pn));
    return Eval(elements);
  }

private:
  enum Operator { INVALID = 0, PLUS, MINUS, MUL, DIV, LP, RP };

  static bool IsParenthesis(Operator op) {
    return op == LP || op == RP;
  }

  static bool GE(Operator left, Operator right) {
    assert(!IsParenthesis(right));
    if (IsParenthesis(left)) return false;

    if (left == MUL || left == DIV) return true;
    if (right == MUL || right == DIV) return false;
    return true;
  }

  static string OperatorToString(Operator op) {
    switch (op) {
    case PLUS: return "+";
    case MINUS: return "-";
    case MUL: return "*";
    case DIV: return "/";
    case LP: return "(";
    case RP: return ")";
    default: assert(false);
    }
  }

  static Operator StringToOperator(const string& s) {
    if (s == "+") return PLUS;
    if (s == "-") return MINUS;
    if (s == "*") return MUL;
    if (s == "/") return DIV;
    if (s == "(") return LP;
    if (s == ")") return RP;
    return INVALID;
  }

  class Element {
  public:
    explicit Element(double num) : num_(num) {};
    explicit Element(Operator op) : op_(op) {};

    bool has_num() const {
      return op_ == INVALID;
    }
    bool has_op() const {
      return op_ != INVALID;
    }

    double num() const {
      assert(has_num());
      return num_;
    }
    Operator op() const {
      assert(has_op());
      return op_;
    }

    string ToString() const {
      return has_num() ? to_string((int)num_) : OperatorToString(op_);
    }

  private:
    double num_ = 0;
    Operator op_ = INVALID;
  };

  // TODO: Support more complicated parsing.
  vector<Element> Parse(const string& s) {
    vector<Element> result;
    std::size_t i = 0;
    while (i < s.size()) {
      if (std::isspace(s.at(i))) {
        ++i; continue;
      }

      if (s.at(i) == '+' || s.at(i) == '-' ||
          s.at(i) == '*' || s.at(i) == '/' ||
          s.at(i) == '(' || s.at(i) == ')') {
        result.emplace_back(StringToOperator(s.substr(i, 1)));
        ++i;
        continue;
      }

      std::size_t next = s.find_first_of("+-*/() ", i);
      next = next == string::npos ? s.size() : next;
      assert(next > i);
      string num = s.substr(i, next - i);
      result.emplace_back(std::stod(num));

      i = next;
    }
    return result;
  }

  vector<Element> ConvertToRPN(const vector<Element>& pn) {
    std::stack<Operator> s;
    vector<Element> result;

    for (const auto& e : pn) {
      if (e.has_num()) {
        result.push_back(e);
      } else if (e.op() == LP) {
        s.push(LP);
      } else if (e.op() == RP) {
        assert(!s.empty());
        while (s.top() != LP) {
          result.emplace_back(s.top());
          s.pop();
        }
        s.pop();
      } else {
        while (!s.empty()) {
          if (GE(s.top(), e.op())) {
            result.emplace_back(s.top());
            s.pop();
          } else {
            break;
          }
        }
        s.push(e.op());
      }
    }
    while (!s.empty()) {
      result.emplace_back(s.top());
      s.pop();
    }

    return result;
  }

  double Eval(const vector<Element>& rpn) {
    std::stack<double> s;
    for (const auto& e : rpn) {
      if (e.has_num()) {
        s.push(e.num());
      } else {
        // TODO: Make this a function.
        assert(!s.empty());
        double right = s.top();
        s.pop();
        assert(!s.empty());
        double left = s.top();
        s.pop();
        switch (e.op()) {
        case PLUS:
          s.push(left + right);
          break;
        case MINUS:
          s.push(left - right);
          break;
        case MUL:
          s.push(left * right);
          break;
        case DIV:
          assert(right != 0);
          s.push(left / right);
          break;
        default:
          assert(false);
        }
      }
    }
    assert(s.size() == 1);
    return s.top();
  }
};

int main(int argc, char** argv) {
  Calculator cal;
  string exp(argv[1]);
  std::cout << exp << endl;
  std::cout << cal.RPN(argv[1]) << " = " << cal.Eval(argv[1]) << std::endl;

  return 0;
}
