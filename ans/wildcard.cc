#include <functional>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
	// More efficient approach. This approach utilizes this fact:
	// If the current matching fails, only fall back to the last *.
	bool isMatch(string s, string p) {
		// Last star pos of p.
		int last_star = -1;
		// The position in s that matches p[0:last_star].
		int last_star_match = -1;

		// i iterates s, j iterates p.
		int i = 0, j = 0;

		auto reset = [&]()-> bool {
			if (last_star < 0) return false;

			last_star_match++;
			j = last_star + 1;
			i = last_star_match + 1;
			return true;
		};

		while (i < s.size()) {
			if (j >= p.size()) {
				if (!reset()) return false;
				continue;
			}

			switch (p[j]) {
			case '*':
				last_star = j;
				last_star_match = i - 1;
				++j;
				break;
			case '?':
				++i; ++j;
				break;
			default:
				if (s[i] == p[j]) {
					++i; ++j;
				} else if (!reset()) {
					return false;
				}
			}
		}

		while (j < p.size() && p[j] == '*') {
			++j;
		}
		return j == p.size();
	}

	bool DPSolution(const string &s, const string &p) {
		vector<vector<bool>> d(p.size() + 1, vector<bool>(s.size() + 1, false));

		d[0][0] = true;
		// d[0][i] = false for i > 0.

		// d[i][0] = true only if p[0, i] = all star.
		for (int i = 1; i < p.size() + 1; ++i) {
			if (p.at(i - 1) == '*') {
				d[i][0] = true;
			} else {
				break;
			}
		}

		for (int i = 1; i <= p.size(); ++i) {
			for (int j = 1; j <= s.size(); ++j) {
				switch (p.at(i - 1)) {
				case '*':
					d[i][j] = d[i][j - 1] || d[i - 1][j];
					break;
				case '?':
					d[i][j] = d[i - 1][j - 1];
					break;
				default:
					d[i][j] = p.at(i - 1) == s.at(j - 1) ? d[i - 1][j - 1] : false;
				}
			}
		}

		return d[p.size()][s.size()];
	}
};

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Invalid argc: " << argc << std::endl;
		return 1;
	}

	string s(argv[1]);
	string p(argv[2]);

	Solution sol;
	if (sol.isMatch(s, p)) {
		std::cout << s << " matches " << p << std::endl;
	} else {
		std::cout << s << " doesn't match " << p << std::endl;
	}

	return 0;
}
