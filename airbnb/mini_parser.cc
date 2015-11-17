// Implement a mini parser:"324" or"[123,456,[788,799,833],[[]],10,[]]"
// Output: 324 or [123,456,[788,799,833],[[]],10,[]].

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <memory>
#include <cassert>

using namespace std;

// Started at 12:00AM.
typedef long long int64;

struct Node {
  int64 num;
  bool has_num = false;
  bool is_empty = true;
  vector<Node*> children;
  explicit Node(int64 _num) : num(_num), has_num(true), is_empty(false) {}
  Node() {}
  ~Node() {
    for (auto* node : children) {
      delete node;
    }
  }

  void Print(bool with_comma) {
    if (has_num) {
      std::cout << num;
    } else {
      std::cout << "[";
      for (int64 i = 0; i < (int64)children.size(); ++i) {
        children[i]->Print(i != (int64)children.size() - 1);
      }
      std::cout << "]";
    }
    if (with_comma) {
      std::cout << ",";
    }
  }
};

// Algorithm:
// For every [, create a Node without num.
// For every num, create a Node with num.
// For every ], pop till ].
Node* MiniParser(const string& input) {
  if (input.empty()) return nullptr;
  stack<Node*> s;

  int64 i = 0;
  while (i < (int64)input.size()) {
    if (input[i] == '[') {
      s.push(new Node());
      ++i;
    } else if (input[i] == ']') {
      // pop.
      vector<Node*> nodes;
      while (!s.empty() && !s.top()->is_empty) {
        nodes.push_back(s.top());
        s.pop();
      }
      assert(!s.empty());
      s.top()->is_empty = false;
      std::reverse(nodes.begin(), nodes.end());
      s.top()->children = std::move(nodes);
      ++i;
    } else if (input[i] == ',' || input[i] == ' ') {
      ++i;
    } else {
      size_t next = input.find_first_of(",[] ", i);
      next = next == string::npos ? input.size() : next;
      int64 num = stol(input.substr(i, next - i));
      s.push(new Node(num));
      i = next;
    }
  }

  assert(s.size() == 1);
  return s.top();
}

int main(int argc, char** argv) {
  std::unique_ptr<Node> node(MiniParser(argv[1]));

  node->Print(false);

  std::cout << "\n";
  return 0;
}
