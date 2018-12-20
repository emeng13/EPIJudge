#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include "test_framework/generic_test.h"

using std::make_unique;
using std::string;
using std::vector;

bool isPalindrome(string s) {
  if (s.length() == 0 || s.length() == 1) {
    return true;
  }

  for (int i = 0; i < s.length() / 2; i++) {
    if (s[i] != s[s.length() - 1 - i]) {
      return false;
    }
  }

  return true;
}

void palindromeDecomp(string input, string remainder, int size, vector<string>* decomp, vector<vector<string>>* resultsPtr) {
  if (size == input.length()) {
    resultsPtr->emplace_back(*decomp);
  }
  else {
    string currDecomp = "";

    for (int i = 0; i < remainder.length(); i++) {
      currDecomp.push_back(remainder[i]);
      size++;
      if (isPalindrome(currDecomp)) {
        decomp->emplace_back(currDecomp);
        palindromeDecomp(input, remainder.substr(i + 1, remainder.length() - i + 1), size, decomp, resultsPtr);
        decomp->pop_back();
      }
    }

  }
}

vector<vector<string>> PalindromeDecompositions(const string& input) {
  vector<vector<string>> result;
  palindromeDecomp(input, input, 0, make_unique<vector<string>>().get(), &result);
  return result;
}
bool Comp(vector<vector<string>> expected, vector<vector<string>> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input"};
  return GenericTestMain(args, "enumerate_palindromic_decompositions.cc",
                         "enumerate_palindromic_decompositions.tsv",
                         &PalindromeDecompositions, &Comp, param_names);
}
