#include "test_framework/generic_test.h"

int SquareRoot(int k) {
  // binary search over interval of numbers
  // if square of mid is equal to k then return k
  // else if square of mid is too large then decrease high to mid - 1
  // else if square of mid is too small then update largest mid seen and increase low to mid + 1
  // all other cases should return 1
  // O(log k) time O(1) space

  if (k == 0) {
     return 0;
  }

  int low = 0;
  int high = k;

  int largestMid = 1;

  while (low <= high) {
    int mid = (low + high) / 2;
    int squared = mid * mid;

    if (squared == k) {
      return mid;
    } else if (squared > k) {
      high = mid - 1;
    } else {
      if (mid > largestMid) {
        largestMid = mid;
      }
      low = mid + 1;
    }
  }

  return largestMid;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
