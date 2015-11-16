#include <vector>
#include <iostream>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

// Given a list of word, output all pair of words that can be formed as
// a palindrome.

vector<pair<string, string>> PalindromeMatching(const vector<string>& words) {
  // Algorithm description:
  // Given any word w, find all words with length <= len(w) that can be formed
  // as palindrome with w. Example:
  // abcc -> ccba, cba, ba, ccb.
  // Then check any of the generated word to see whether it is in the list,
  // if yes, output the pair. This guarantees uniqueness.
  // Time complexity: O(n * L * L).

  // Questions to clarify: abc, cba, do i need to output twice?. I guess yes.
  // Should I consider empty string?

  std::unordered_set<string> words_set(words.begin(), words.end());

  vector<pair<string, string>> results;
  std::unordered_set<string> palindromes;
  bool contains_empty = false;
  for (const string& w : words) {
    if (w.empty()) {
      contains_empty = true;
      continue;
    }

    string rw(w);
    std::reverse(rw.begin(), rw.end());

    if (w == rw) palindromes.insert(w);

    // w is on left.
    for (int i = 1; i < w.size(); ++i) {
      if (w.substr(w.size() - i, i) == rw.substr(0, i) &&
          words_set.count(rw.substr(i))) {
        results.push_back(make_pair(w, rw.substr(i)));
      }
    }

    // w is on the right.
    for (int i = 1; i < rw.size(); ++i) {
      if (rw.substr(rw.size() - i, i) == w.substr(0, i) &&
          words_set.count(rw.substr(0, rw.size() - i))) {
        results.push_back(make_pair(rw.substr(0, rw.size() - i), w));
      }
    }

    if (words_set.count(rw))
      results.push_back(make_pair(w, rw));
  }

  if (contains_empty) {
    for (auto& s : palindromes) {
      results.push_back(make_pair(s, ""));
    }
  }

  return results;
}

int main(int argc, char** argv) {
  vector<string> words;
  for (int i = 1; i < argc; ++i) {
    words.push_back(argv[i]);
    std::cout << words.back() << " ";
  }
  std::cout << "END" << endl;

  auto r = PalindromeMatching(words);
  for (auto& p : r) {
    std::cout << p.first << " " << p.second << std::endl;
  }
  return 0;
}
