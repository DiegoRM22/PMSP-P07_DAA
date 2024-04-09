
#ifndef INTER_SWAP_LOCAL_SEARCH_H
#define INTER_SWAP_LOCAL_SEARCH_H

#include <vector>

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "../local-search.h"

class InterSwapLocalSearch : public LocalSearch {
 public:
  InterSwapLocalSearch(Problem problem, Solution solution) : LocalSearch(problem, solution) {}
  std::vector<Solution> GenerateNeighbors(const Solution& solution) override;
};

#endif // INTER_SWAP_LOCAL_SEARCH_H