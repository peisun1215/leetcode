#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// true: blocked.
struct D {
  int r = 0;
  int c = 0;

  D(int _r, int _c) : r(_r), c(_c) {}
};

enum STATE {
  BLOCKED = 0,
  NOT_VISITED = 1,
  START = 2,
  TOP = 3,
  LEFT = 4,
  BOT = 5,
  RIGHT = 6
};

string PrintPath(const vector<vector<STATE>>& path_info);

string FindPath(vector<vector<bool>>& grid) {
  if (grid.empty()) return "";
  if (grid[0].empty()) return "";

  // -2, blocked. -1, not visited. 0: none. 1: top, 2: left, 3: bot, 4: right.
  vector<vector<STATE>> path_info(grid.size(),
                                  vector<STATE>(grid[0].size(), NOT_VISITED));
  for (int i = 0; i < grid.size(); ++i){
    for (int j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j]) {
        path_info[i][j] = BLOCKED;
      }
    }
  }

  std::queue<D> q;
  q.emplace(0, 0);
  path_info[0][0] = START;

  while (!q.empty()) {
    auto front = q.front();
    q.pop();
    if (front.r == grid.size() - 1 && front.c == grid[0].size() - 1) {
      return PrintPath(path_info);
    }

    // top.
    if (front.r > 0 && path_info[front.r - 1][front.c] == NOT_VISITED) {
      path_info[front.r - 1][front.c] = BOT;
      q.emplace(front.r - 1, front.c);
    }
    // bot.
    if (front.r < grid.size() - 1 &&
        path_info[front.r + 1][front.c] == NOT_VISITED) {
      path_info[front.r + 1][front.c] = TOP;
      q.emplace(front.r + 1, front.c);
    }
    // left.
    if (front.c > 0 && path_info[front.r][front.c - 1] == NOT_VISITED) {
      path_info[front.r][front.c - 1] = RIGHT;
      q.emplace(front.r, front.c - 1);
    }
    // right.
    if (front.c < grid[0].size() - 1 &&
        path_info[front.r][front.c + 1] == NOT_VISITED) {
      path_info[front.r][front.c + 1] = LEFT;
      q.emplace(front.r, front.c + 1);
    }
  }
  return "No path!";
}

string PrintPath(const vector<vector<STATE>>& path_info) {
  int r = path_info.size() - 1;
  int c = path_info.at(0).size() - 1;

  auto point = [](int r, int c)->string {
    return "(" + std::to_string(r) + "," + std::to_string(c) + ")";
  };

  string result;
  while (1) {
    result = point(r, c) + result;
    switch (path_info.at(r).at(c)) {
    case START:
      return result;
    case TOP:
      --r;
      break;
    case LEFT:
      --c;
      break;
    case BOT:
      ++r;
      break;
    case RIGHT:
      ++c;
      break;
    default:
      assert(false);
    }
  }
  return result;
}


int main(int argc, char** argv) {
  vector<vector<bool>> grid = {
    {0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {0, 1, 1}, {0, 0, 0}
  };

  std::cout << FindPath(grid) << std::endl;

  return 0;
}
