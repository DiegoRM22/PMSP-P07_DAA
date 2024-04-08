
#ifndef GRAASP_ALGORITHM_H
#define GRAASP_ALGORITHM_H

#include <vector>

#include "../problem/problem.h"
#include "../solution/solution.h"

class GRASPAlgorithm {
 public:
  GRASPAlgorithm(Problem problem) : problem_(problem) {}
  Solution Solve();
  int CalculatesHeuristic(const Solution& solution, int assignment);
  int GetTCT() const { return TCT; }
  Solution executesNTimes(int iterations);
 private:
  Problem problem_;
  int TCT = 0;
};

#endif // GRAASP_ALGORITHM_H