#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

typedef long long int64;

namespace {
  void WordsWithED1(std::unordered_set<string>& words) {
    std::unordered_set<string> results;
    for (auto& w : words) {
      // Insert. (|w| + 1) * 26.
      for (int64 i = 0; i <= (int64)w.size(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
          results.insert(w.substr(0, i) + j + w.substr(i));
        }
      }
      // Delete. |w|
      for (int64 i = 0; i < (int64)w.size(); ++i) {
        results.insert(w.substr(0, i) + w.substr(i + 1));
      }
      // Replace. |w| * 25
      for (int64 i = 0; i < (int64)w.size(); ++i) {
        for (char j = 'a'; j <= 'z'; ++j) {
          if (j == w.at(i)) continue;
          results.insert(w.substr(0, i) + j + w.substr(i + 1));
        }
      }
    }
    for (auto& r : results) {
      words.emplace(std::move(r));
    }
  }
}

// Every word is lowercase.
vector<string> WordsWithEDK(const std::unordered_set<string>& dict,
                            const string& word, int64 edit_distance) {
  std::unordered_set<string> words;
  words.insert(word);
  while (edit_distance > 0) {
    WordsWithED1(words);
    --edit_distance;
  }
  vector<string> results;
  for (const string& w : words) {
    if (dict.count(w)) {
      results.emplace_back(std::move(w));
    }
  }
  return results;
}



int main(int argc, char** argv) {
  std::unordered_set<string> dict = {"hot", "dog", "dogs", "hat", "hottt"};
  for (const string& d : dict) {
    std::cout << d << " ";
  }
  std::cout << std::endl;

  vector<string> words = WordsWithEDK(dict, "hot", 2);

  for (auto& w : words) {
    std::cout << w << " ";
  }
  std::cout << endl;
  return 0;
}
