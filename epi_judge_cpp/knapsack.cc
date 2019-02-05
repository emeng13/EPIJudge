#include <algorithm>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::max;
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  vector<vector<int>> values(items.size() + 1, vector<int>(capacity + 1, 0));

  for (int i = 0; i <= items.size(); i++) {
    for (int j = 0; j <= capacity; j++) {
      if (i == 0 || j == 0) {
        values[i][j] = 0;
      }
      else if (items[i-1].weight <= j) {
        int without = values[i-1][j];
        int with = values[i-1][j - items[i-1].weight] + items[i-1].value;
        values[i][j] = max(without, with);
      }
      else {
        values[i][j] = values[i-1][j];
      }
    }
  }

  return values[items.size()][capacity];
}
template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
