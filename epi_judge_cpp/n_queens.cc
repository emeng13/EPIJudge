#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <vector>
#include "test_framework/generic_test.h"

using std::make_unique;
using std::vector;

bool isValid(const vector<int>& placement) {
  // check validity of newest addition
  int newQueenRow = placement.size() - 1;
  for (int i = 0; i < newQueenRow; i++) {
    int diff = placement[i] - placement[newQueenRow];

    // same col
    if (diff == 0) {
      return false;
    }

    // check for diagonal
    if ((diff == i - newQueenRow) || (diff == newQueenRow - i)) {
      return false;
    }
  }

  return true;
}

void addQueen(int n, int row, vector<int>* placement, vector<vector<int>>* resultPtr) {
  // all queens placed successfully so add placement to result
  if  (row == n) {
    resultPtr->emplace_back(*placement);
  }

  else {
    // try adding queen at each col in current row
    for (int col = 0; col < n; col++) {
      placement->emplace_back(col);
      
      // valid, try adding queen at next row and check validity
      if (isValid(*placement)) {
        addQueen(n, row + 1, placement, resultPtr);
      }
      // invalid or backtrack, remove queen
      placement->pop_back();
    }
  }
}

vector<vector<int>> NQueens(int n) {
  vector<vector<int>> result;
  addQueen(n, 0, make_unique<vector<int>>().get(), &result);
  return result;
}

bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
  std::sort(std::begin(a), std::end(a));
  std::sort(std::begin(b), std::end(b));
  return a == b;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens, &Comp,
                         param_names);
}
