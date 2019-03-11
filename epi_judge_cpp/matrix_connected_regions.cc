#include <deque>
#include <queue>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::queue;
using std::vector;

struct Coordinate {
  int x, y;
};

bool isValid(const vector<deque<bool>>* image_ptr, int x, int y, bool color) {
  int maxX = image_ptr->size();
  int maxY = (*image_ptr)[0].size();

  if (x < 0 || x >= maxX || y < 0 || y >= maxY) {
    return false;
  }

  if ((*image_ptr)[x][y] != color) {
    return false;
  }

  return true;
}

void flipRegionBFS(int x, int y, bool color, vector<deque<bool>>* image_ptr) {
  queue<Coordinate> q;
  q.push(Coordinate{x, y});
  while (!q.empty()) {
    Coordinate curr = q.front();
    q.pop();
    (*image_ptr)[curr.x][curr.y] = !color;

    if (isValid(image_ptr, curr.x - 1, curr.y, color)) {
      q.push(Coordinate{curr.x - 1, curr.y});
    }
    if (isValid(image_ptr, curr.x, curr.y + 1, color)) {
      q.push(Coordinate{curr.x, curr.y + 1});
    }
    if (isValid(image_ptr, curr.x + 1, curr.y, color)) {
      q.push(Coordinate{curr.x + 1, curr.y});
    }
    if (isValid(image_ptr, curr.x, curr.y - 1, color)) {
      q.push(Coordinate{curr.x, curr.y - 1});
    }
  }
}

void flipRegionDFS(int x, int y, bool color, vector<deque<bool>>* image_ptr) {
  (*image_ptr)[x][y] = !color;

  if (isValid(image_ptr, x - 1, y, color)) {
    flipRegionDFS(x - 1, y, color, image_ptr);
  }
  if (isValid(image_ptr, x, y + 1, color)) {
    flipRegionDFS(x, y + 1, color, image_ptr);
  }
  if (isValid(image_ptr, x + 1, y, color)) {
    flipRegionDFS(x + 1, y, color, image_ptr);
  }
  if (isValid(image_ptr, x, y - 1, color)) {
    flipRegionDFS(x, y - 1, color, image_ptr);
  }
}

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  bool color = (*image_ptr)[x][y];
  flipRegionBFS(x, y, color, image_ptr);
  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
