#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int NumberOfWays(int n, int m) {
  vector<int> arr;

  if (n == 1 || m == 1) {
    return 1;
  }

  for (int x = 0; x < m; x++) {
    arr.push_back(1);
  }

  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      arr[j] = arr[j] + arr[j-1];
    }
  }

  return arr[m-1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
