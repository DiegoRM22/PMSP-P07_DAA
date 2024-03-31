
#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H

#include <vector>

#include "../problem/problem.h"
#include "../solution/solution.h"

class GreedyAlgorithm {
 public:
  GreedyAlgorithm(Problem problem) : problem_(problem) {}
  Solution Solve();
 private:
  Problem problem_;
};

#endif // GREEDY_ALGORITHM_H