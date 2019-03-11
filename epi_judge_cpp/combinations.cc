#include <memory>
#include <vector>
#include "test_framework/generic_test.h"

using std::make_unique;
using std::vector;

void kSubset(int n, int k, int idx, vector<int>* subset, vector<vector<int>>* resultsPtr) {
  if (size(*subset) == k) {
    resultsPtr->emplace_back(*subset);
    return;
  }
  else {
    const int remainder = k - size(*subset);
    for (int i = idx;  i <= n && remainder <= n - i + 1; ++i) {
      subset->emplace_back(i);
      kSubset(n, k, i + 1, subset, resultsPtr);
      subset->pop_back();
    }
  }
}

vector<vector<int>> Combinations(int n, int k) {
  vector<vector<int>> result;
  kSubset(n, k, 1, make_unique<vector<int>>().get(), &result);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "combinations.cc", "combinations.tsv", &Combinations,
      &UnorderedComparator<std::vector<std::vector<int>>>, param_names);
}
