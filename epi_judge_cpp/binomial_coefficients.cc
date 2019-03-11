#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int ComputeBinomialCoefficient(int n, int k) {
  vector<int> arr;
  if (k == 0 || n == k) {
    return 1;
  }

  for (int x = 0; x <= k; x++) {
    arr.push_back(1);
  }

  for (int i = 1; i < n; i++) {
    for (int j = std::min(i, k); j > 0; j--) {
      arr[j] = arr[j] + arr[j-1];
    }
  }

  return arr[k];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
