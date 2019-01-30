#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int min(int a, int b, int c) {
  if (a <= b && a <= c) {
    return a;
  } else if (b <= a && b <= c) {
    return b;
  } else {
    return c;
  }
}

int LevenshteinDistance(const string& A, const string& B) {
  int m = A.length();
  int n = B.length();

  vector<vector<int>> distances(m+1, vector<int> (n+1, 0));
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0) {
        distances[i][j] = j;
      } else if (j == 0) {
        distances[i][j] = i;
      } else {
        distances[i][j] = min(distances[i-1][j-1] + (A.at(i-1) == B.at(j-1) ? 0 : 1),
                              distances[i][j-1] + 1,
                              distances[i-1][j] + 1);
      }
    }
  }
  return distances[m][n];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
