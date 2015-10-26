#include "common/kmp/kmp.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
	string ShortestPalindrome(const string &s) {
		common::kmp::KMP kmp(s);

		string reverse_s(s);
		std::reverse(reverse_s.begin(), reverse_s.end());

		// Find the longgest prefix of s that is also a suffix of reverse_s.
		int si = 0;  // for s.
		int ri = 0;  // for reverse_s.

		while (ri < reverse_s.size()) {
			if (reverse_s.at(ri) == s.at(si)) {
				++ri; ++si;
			} else if (si == 0) {
				++ri;
			} else {
				si = kmp.Prefix(si);
			}
		}

		int longgest_prefix = si;

		return reverse_s.substr(0, s.size() - si) + s;
	}
};

int main(int argc, char** argv) {
	if (argc != 2) return 1;

	string s = argv[1];

	Solution ss;
	std::cout << ss.ShortestPalindrome(s) << std::endl;
}
