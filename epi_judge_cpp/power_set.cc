#include <algorithm>
#include <vector>
#include "test_framework/generic_test.h"

using std::find;
using std::make_unique;
using std::vector;

// v1 timeout
// void powerSet(vector<int> set, vector<vector<int>>* resultPtr) {
//   if (set.size() == 0) {
//     return;
//   } 
//   else {
//     if (std::find(resultPtr->begin(), resultPtr->end(), set) == resultPtr->end()) {
//       resultPtr->emplace_back(set);
//     }

//     for (int i = 0; i < set.size(); i++) {
//       vector<int> minusSet = set;
//       minusSet.erase(minusSet.begin() + i);

//       powerSet(minusSet, resultPtr);
//     }
//   } 
// }

void powerSet(vector<int> set, int n, vector<int>* subset, vector<vector<int>>* resultsPtr) {
  if (set.size() == n) {
    resultsPtr->emplace_back(*subset);
  }
  else {
    subset->emplace_back(set.at(n));

    powerSet(set, n + 1, subset, resultsPtr);

    subset->pop_back();

    powerSet(set, n + 1, subset, resultsPtr);
  }
}

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  vector<vector<int>> result;
  powerSet(input_set, 0, make_unique<vector<int>>().get(), &result);

  // v1
  // result.emplace_back(vector<int>());
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(
      args, "power_set.cc", "power_set.tsv", &GeneratePowerSet,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
