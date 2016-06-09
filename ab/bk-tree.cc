// Build a data structure to look up words with edit distance <= k for a given
// word (w) from a dict (d).

// Edit distance key observation:
// d(x, y) = d(y, x).
// d(x, x) = 0.
// d(x, y) + d(y, z) >= d(x, z).
//
// This is a valid distance metric. We can use BK tree (one metric tree).
//
// Given any root a,
// d(x, w) = d(w, x) <= K.
// d(x, a) >= d(x, w) - d(w, a) >= 0. d(x, a) >= d(a, w) - d(w, x) >= d(a, w) - K.
// d(x, a) <= d(x, w) + d(w, a) <= d(a, w) + K.
// So we just need to look at everything between |d(a, w) + K| and d(a, w) - K.

#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <unordered_set>
#include <map>
#include <string>

using namespace std;

typedef long long int64;

class BKTree {
public:
  struct Node {
    string w;
    map<int64, Node*> children;
    explicit Node(const string& _w) : w(_w) {}
    ~Node() {
      for (const auto& kv : children) {
        assert(kv.second);
        delete kv.second;
      }
    }

    // key <= upper, key >= lower.
    vector<Node*> NodesWithRange(int64 lower, int64 upper) {
      auto u = children.upper_bound(upper);
      auto l = children.upper_bound(lower);
      vector<Node*> result;
      for (auto it = l; it != u; ++it) {
        result.push_back(it->second);
      }
      return result;
    }
  };

  explicit BKTree(const std::unordered_set<string>& dict) {
    assert(!dict.empty());
    auto it = dict.begin();
    root_.reset(new Node(*it));

    std::cout << "Root = " << *it << endl;

    ++it;
    BuildTree(dict, root_.get(), it);

    std::cout << "BK tree is built." << endl;
  }

  ~BKTree() {}

  vector<string> WordsLEDistance(const string& word, int64 distance) {
    vector<string> result;
    WordsLEDistance(word, distance, root_.get(), result);
    return result;
  }

private:
  void WordsLEDistance(const string& word, int64 distance,
                       Node* root, vector<string>& result) {
    int64 ed = EditDistance(word, root->w);
    if (ed <= distance) result.push_back(root->w);

    int64 upper = ed + distance;
    int64 lower = std::max<int64>(ed - distance, 0);
    auto nodes = root->NodesWithRange(lower, upper);
    for (auto* node : nodes) {
      WordsLEDistance(word, distance, node, result);
    }
  }

  void BuildTree(const std::unordered_set<string>& dict,
                 Node* root,
                 std::unordered_set<string>::const_iterator it) {
    if (it == dict.end()) return;
    assert(root);

    int64 distance = EditDistance(root->w, *it);
    auto tmp = root->children.find(distance);
    // No found.
    if (tmp == root->children.end()) {
      root->children[distance] = new Node(*it++);
    } else {
      root = tmp->second;
    }

    BuildTree(dict, root, it);
  }

  // DP.
  int64 EditDistance(const string& s1, const string& s2) {
    // s1 = abcd, s2 = bedf
    // d[i][j] = d[i-1][j-1] (s1[i - 1] == s2[j - 1])
    //           d[i-1][j] + 1 (delete s1[i - 1]).
    //           d[i][j-1] + 1 (insert s2[j - 1] after s[i - 1]).
    //           d[i-1][j-1] + 1 (replace).
    // d[0][j] = j.
    // d[i][0] = i.

    vector<vector<int64>> d(s1.size() + 1, vector<int64>(s2.size() + 1, 0));

    // Init.
    // d[0][i].
    for (int64 i = 1; i <= (int64)s2.size(); ++i) {
      d[0][i] = i;
    }
    // d[i][0].
    for (int64 i = 1; i <= (int64)s1.size(); ++i) {
      d[i][0] = i;
    }

    for (int64 i = 1; i <= (int64)s1.size(); ++i) {
      for (int64 j = 1; j <= (int64)s2.size(); ++j) {
        if (s1.at(i - 1) == s2.at(j - 1)) {
          d[i][j] = d[i - 1][j - 1];
        } else {
          d[i][j] = d[i - 1][j - 1] + 1;
          d[i][j] = std::min(d[i][j], d[i][j - 1] + 1);
          d[i][j] = std::min(d[i][j], d[i - 1][j] + 1);
        }
      }
    }

    return d[s1.size()][s2.size()];
  }

  std::unique_ptr<Node> root_;
};


int main(int argc, char** argv) {
  std::unordered_set<string> dict = {
    "hott", "hot", "abc", "hat", "hats", "dog", "fogggggg"};

  BKTree tree(dict);

  {
    auto words = tree.WordsLEDistance("got", 3);
    for (auto& i : words) cout << i << endl;
  }

  string word;
  int64 distance;
  while (1) {
    std::cin >> word >> distance;
    auto words = tree.WordsLEDistance(word, distance);

    for (auto& w : words) {
      std::cout << w << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
