// Parse one line.
// 12:53.

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

typedef long long int64;

void Strip(string& s) {
  int64 i = 0;
  while (i < (int64)s.size() && isspace(s[i])) {
    ++i;
  }
  s.erase(0, i);

  i = (int64)s.size();
  while (i >= 0 && isspace(s[i])) {
    s.pop_back();
    --i;
  }
  if (s.size() >= 2 && s.front() == '\"' && s.back() == '\"') {
    s.erase(0, 1);
    s.pop_back();
  }
}

// Split based on ",".
vector<string> ParseOneLine(const string& csv) {
  vector<string> result;

  // start: where the next word starts (inclusive).
  int64 start = 0;
  // Where the next word ends (exclusive).
  int64 end = 0;
  // Number of quotes (") within [start, end).
  int64 num_quotes = 0;
  while (end < (int64)csv.size()) {
    if (csv[end] == ',') {
      if (num_quotes % 2 != 0) {
        ++end;
        continue;
      }
      result.push_back(csv.substr(start, end - start));
      start = end + 1;
      end = start;
      num_quotes = 0;
    } else if (csv[end] == '\\') {
      // If the input is malformed, treat this specially.
      end += 2;
    } else if (csv[end] == '\"') {
      num_quotes++;
      end++;
    } else {
      end++;
    }
  }

  // The last one.
  if (start < (int64)csv.size()) {
    result.push_back(csv.substr(start));
  }

  for (auto& s : result) {
    // Strip spaces and quotes.
    Strip(s);
  }

  return result;
}


int main(int argc, char** argv) {
  string one_line = R""(pei,  ""\"Google"" \,\n, 21, "afab , " " ,,,",)"";
  vector<string> result = ParseOneLine(one_line);
  for (auto& r : result) {
    std::cout << r << endl;
  }
  return 0;
}
