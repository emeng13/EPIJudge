#include <cstdlib>
#include <iterator>
#include <memory>
#include <vector>
#include "test_framework/generic_test.h"

using std::make_unique;
using std::vector;

void generatePermutations(vector<int> A, vector<int>* permutation, vector<vector<int>>* resultPtr) {
  if (A.size() == 0) {
    resultPtr->emplace_back(*permutation);
  }

  else {
    for (int i = 0; i < A.size(); i++) {
      permutation->emplace_back(A.at(i));

      vector<int> minusA = A;
      minusA.erase(minusA.begin() + i);

      generatePermutations(minusA, permutation, resultPtr);

      permutation->pop_back();
    }
  }
}

vector<vector<int>> Permutations(vector<int> A) {
  vector<vector<int>> result;
  generatePermutations(A, make_unique<vector<int>>().get(), &result);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "permutations.cc", "permutations.tsv", &Permutations,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
