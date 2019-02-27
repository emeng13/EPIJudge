#include <tuple>
#include <unordered_map>
#include <vector>
#include "test_framework/generic_test.h"
using std::tuple;
using std::unordered_map;
using std::vector;

bool checkPattern(const vector<vector<int>>& grid, int m, int n, const vector<int>& pattern, int idx, unordered_map<vector<int>, int>* notFound, int i , int j) {
  // nothing to check so pattern exists
  if (pattern.size() == 0) {
    return true;
  }

  // location is out of bounds
  if (i >= m || i < 0 || j >= n || j < 0) {
    return false;
  }

  // previous not found already
  vector<int> custom;
  custom.push_back(i);
  custom.push_back(j);
  custom.push_back(pattern[idx]);

  if (notFound->find(custom) != notFound->end()) {
    return false;
  }

  if (checkPattern(grid, m, n, pattern, idx++, notFound, i - 1, j)) {
    return true;
  }

  notFound->emplace(custom, 1);
  return false;
}

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
  unordered_map<vector<int>, int> notFound;
  int m = grid.size();
  int n = grid[0].size();

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (checkPattern(grid, m, n, pattern, 0, &notFound, i, j)) {
        return true;
      }
    }
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"grid", "pattern"};
  return GenericTestMain(args, "is_string_in_matrix.cc",
                         "is_string_in_matrix.tsv", &IsPatternContainedInGrid,
                         DefaultComparator{}, param_names);
}
