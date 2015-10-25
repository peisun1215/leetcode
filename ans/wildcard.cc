#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Solution {
public:
	// More efficient approach. This approach utilizes this fact:
	bool isMatch(string s, string p) {
		
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
	if (sol.DPSolution(s, p)) {
		std::cout << s << " matches " << p << std::endl;
	} else {
		std::cout << s << " doesn't match " << p << std::endl;
	}

	return 0;
}
