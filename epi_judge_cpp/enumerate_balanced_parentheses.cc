#include <string>
#include <vector>
#include "test_framework/generic_test.h"

using std::string;
using std::vector;

void matchParens(int k, int countL, int countR, string parens, vector<string>* resultsPtr) {
  if (parens.length() == 2*k) {
    resultsPtr->emplace_back(parens);
  }
  else {
    if (countL < k) {
      matchParens(k, countL + 1, countR, parens + "(", resultsPtr);
    }
    if (countR < countL) {
      matchParens(k, countL, countR + 1, parens + ")", resultsPtr);
    }
  }
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  vector<string> result;
  matchParens(num_pairs, 0, 0, "", &result);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses,
                         &UnorderedComparator<vector<string>>, param_names);
}
