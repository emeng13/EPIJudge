#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int>& A) {
  // searching for pivot point, if A[mid] is less than element before/greater than element after, then pivot is mid/mid + 1
  // pivot is not mid, but if A[mid] is less than element at low, then pivot will be between low and mid so update high to mid - 1
  // else implied A[mid] is greater than element at high and pivot will be between mid and high so update low to mid + 1
  // corner cases of size 1 and unrotated
  // O(log n) time O(1) space

  if  (A.size() == 1 || A[0] < A[A.size() - 1]) {
    return 0;
  }

  int low = 0;
  int high = A.size() - 1;

  while (low < high) {
    int mid = (low + high)/2;
    
    if (A[mid] < A[mid - 1]) {
      return mid;
    }

    if (A[mid] > A[mid + 1]) {
      return mid + 1;
    }

    if (A[mid] < A[low]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
