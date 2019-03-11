#include <algorithm>
#include <bitset>
#include <cstdlib>
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

// v1
// void powerSet(vector<int> set, int n, vector<int>* subset, vector<vector<int>>* resultsPtr) {
//   if (set.size() == n) {
//     resultsPtr->emplace_back(*subset);
//   }
//   else {
//     subset->emplace_back(set.at(n));

//     powerSet(set, n + 1, subset, resultsPtr);

//     subset->pop_back();

//     powerSet(set, n + 1, subset, resultsPtr);
//   }
// }

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  vector<vector<int>> result;

  const int size = input_set.size();

  for (int i = 0; i < pow(2.0, size); i++) {
    std::bitset<32> bits(i);
    vector<int> subset = vector<int>();
    for (int j = 0; j < size; j++) {
      if (bits[j] != 0) {
        subset.emplace_back(input_set[j]);
      }
    }
    result.emplace_back(subset);
  }

  // v1
  // powerSet(input_set, 0, make_unique<vector<int>>().get(), &result);

  // v1 timeout
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
