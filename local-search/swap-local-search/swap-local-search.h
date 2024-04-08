
#ifndef SWAP_LOCAL_SEARCH_H
#define SWAP_LOCAL_SEARCH_H

#include <vector>

#include "../../problem/problem.h"
#include "../../solution/solution.h"

class SwapLocalSearch {
 public:
  SwapLocalSearch(Problem problem, Solution solution) : problem_(problem), currentSolution_(solution) {}
  Solution Solve();
  std::vector<Solution> GenerateNeighbors(const Solution& solution);
  Solution FindBetterNeighbor(const std::vector<Solution>& neighbors);
  bool IsLocalOptimum(const Solution& solution, const std::vector<Solution>& neighbors);
 private:
  Solution currentSolution_;
  Problem problem_;
};

#endif // SWAP_LOCAL_SEARCH_H