#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::queue;
using std::string;
using std::vector;

struct Coordinate {
  int x, y;
};

bool isValid(const vector<vector<char>>* board, int x, int y) {
  int maxX = board->size();
  int maxY = (*board)[0].size();

  if (x < 0 || x >= maxX || y < 0 || y >= maxY) {
    return false;
  }

  if ((*board)[x][y] != 'W') {
    return false;
  }

  return true;
}

void markAsKeepBFS(vector<vector<char>>* board_ptr, int x, int y) {
  queue<Coordinate> q;
  q.push(Coordinate{x, y});

  while (!q.empty()) {
    Coordinate curr = q.front();
    q.pop();

    (*board_ptr)[curr.x][curr.y] = 'K';
    if (isValid(board_ptr, curr.x - 1, curr.y)) {
      q.push(Coordinate{curr.x - 1, curr.y});
    }
    if (isValid(board_ptr, curr.x, curr.y + 1)) {
      q.push(Coordinate{curr.x, curr.y + 1});
    }
    if (isValid(board_ptr, curr.x + 1, curr.y)) {
      q.push(Coordinate{curr.x + 1, curr.y});
    }
    if (isValid(board_ptr, curr.x, curr.y - 1)) {
      q.push(Coordinate{curr.x, curr.y - 1});
    }

  }
}

void markAsKeepDFS(vector<vector<char>>* board_ptr, int x, int y) {
  (*board_ptr)[x][y] = 'K';

  if (isValid(board_ptr, x - 1, y)) {
    markAsKeepDFS(board_ptr, x - 1, y);
  }
  if (isValid(board_ptr, x, y + 1)) {
    markAsKeepDFS(board_ptr, x, y + 1);
  }
  if (isValid(board_ptr, x + 1, y)) {
    markAsKeepDFS(board_ptr, x + 1, y);
  }
  if (isValid(board_ptr, x, y - 1)) {
    markAsKeepDFS(board_ptr, x, y - 1);
  }
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
  int maxX = board_ptr->size();
  int maxY = (*board_ptr)[0].size();

  // first and last cols
  for (int i = 0; i < maxX; i++) {
    if ((*board_ptr)[i][0] == 'W') {
      markAsKeepBFS(board_ptr, i, 0);
    }

    if ((*board_ptr)[i][maxY - 1] == 'W') {
      markAsKeepBFS(board_ptr, i, maxY - 1);
    }
  }

  // first and last rows
  for (int j = 1; j < maxY - 1; j++) {
    if ((*board_ptr)[0][j] == 'W') {
      markAsKeepBFS(board_ptr, 0, j);
    }

    if ((*board_ptr)[maxX - 1][j] == 'W') {
      markAsKeepBFS(board_ptr, maxX - 1, j);
    }
  }

  // update to appropriate color
  for (int i = 0; i < maxX; i++) {
    for (int j = 0; j < maxY; j++) {
      if ((*board_ptr)[i][j] == 'W') {
        (*board_ptr)[i][j] = 'B';
      }
      else if ((*board_ptr)[i][j] == 'K') {
        (*board_ptr)[i][j] = 'W';
      }
    }
  }

  return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
