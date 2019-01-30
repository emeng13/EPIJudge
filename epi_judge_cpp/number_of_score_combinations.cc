#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using std::cout;
using std::endl;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  vector<int> arr;

  for (int x = 0; x <= final_score; x++) {
      if (x == 0) {
        arr.push_back(1);
      } else {
        arr.push_back(0);
      }
  }

  for (int i = 0; i < individual_play_scores.size(); i++) {
    for (int j = individual_play_scores[i]; j <= final_score; j++) {
      arr[j] += arr[j - individual_play_scores[i]];  
    }
  }

  return arr[final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
