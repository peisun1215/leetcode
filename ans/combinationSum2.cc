#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		std::sort(candidates.begin(), candidates.end());
    vector<vector<int>> out;
		vector<int> prefix;
		combinationSum2(candidates, 0, target, out, prefix);
		return out;
	}

	void combinationSum2(vector<int>& candidates, int start, int target,
											 vector<vector<int>>& out, vector<int>& prefix) {
		if (target == 0) {
			out.push_back(prefix);
			return;
		}

		int last_candidate = -1;
		for (int i = start; i < candidates.size(); ++i) {
			if (candidates[i] == last_candidate) continue;
			if (candidates[i] <= target) {
				last_candidate = candidates[i];
				prefix.push_back(candidates[i]);
				combinationSum2(candidates, i + 1, target - candidates[i], out, prefix);
				prefix.pop_back();
			} else {
				break;
			}
		}
	}
};

int main(int argc, char** argv) {
	Solution s;
	vector<int> c = {1, 1, 1, 1, 2};
	vector<vector<int>> res = s.combinationSum2(c, 2);
	for (auto &k : res) {
		for (auto &j : k) {
			std::cout << j << " ";
		}
		std::cout << "\n";
	}

	return 0;
}
