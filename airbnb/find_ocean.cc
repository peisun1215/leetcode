#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>

using namespace std;  // Only for interview.

typedef long long int64;

void print(vector<string>& world) {
  for (auto& s : world) {
    std::cout << s << endl;
  }
}

void FindOcean(int64 i, int64 j, vector<string>& world) {
  if (world.empty()) return;

  assert(i >= 0 && j >= 0);
  assert(static_cast<int64>(world.size()) > i);
  assert(static_cast<int64>(world.at(i).size()) > j);

  if (world.at(i).at(j) == 'L') return;

  stack<pair<int64, int64>> q;
  q.emplace(i, j);
  world[i][j] = 'O';

  auto add_if_valid = [&](int64 r, int64 c) {
    if (r < 0 || r >= static_cast<int64>(world.size())) return;
    if (c < 0 || c >= static_cast<int64>(world[r].size())) return;
    if (world[r][c] == 'W') {
      world[r][c] = 'O';
      q.emplace(r, c);
    }
  };

  while (!q.empty()) {
    auto f = q.top();
    q.pop();
    // top.
    add_if_valid(f.first - 1, f.second);
    // bot.
    add_if_valid(f.first + 1, f.second);
    // left.
    add_if_valid(f.first, f.second - 1);
    // right.
    add_if_valid(f.first, f.second + 1);
  }
}


int main(int argc, char** argv) {
  vector<string> world = {
    "WWLLLW",
    "WLWLWWW",
    "WWWLWW"
  };
  print(world);
  FindOcean(0, 1, world);
  print(world);
  return 0;
}
