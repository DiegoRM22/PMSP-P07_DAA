
#ifndef SWAP_LOCAL_SEARCH_H
#define SWAP_LOCAL_SEARCH_H

#include <vector>

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "../local-search.h"

class SwapLocalSearch : public LocalSearch {
 public:
  SwapLocalSearch(Problem problem, Solution solution) : LocalSearch(problem, solution) {}
  std::vector<Solution> GenerateNeighbors(const Solution& solution) override;
};

#endif // SWAP_LOCAL_SEARCH_H