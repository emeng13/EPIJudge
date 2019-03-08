#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

// O(log n) time O(1) space
int SearchFirstOfK(const vector<int>& A, int k) {
  // approach 1
  // O(n) time O(1) space
  // run binary search until A[mid] = k then iterate backwards until no more k

  // approach 2
  // run binary search normally except instead of return mid when A[mid] = k, track lastFound and continue searching with high = mid - 1
  // while loop bound should be low <= high
  // when loop breaks, lastFound should hold first occurrence of k

  int low = 0;
  int high = A.size() - 1;
  int lastFound = -1;
 
  while (low <= high) {
    int mid = (low + high) / 2;
    if (A[mid] == k) {
      // update
      lastFound = mid;
      high = mid - 1;
    } else if (A[mid] < k) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return lastFound;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
