
#ifndef REINSERT_LOCAL_SEARCH_H
#define REINSERT_LOCAL_SEARCH_H

#include <vector>

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "../local-search.h"

class ReinsertLocalSearch : public LocalSearch {
 public:
  ReinsertLocalSearch(Problem problem, Solution solution) : LocalSearch(problem, solution) {}
  std::vector<Solution> GenerateNeighbors(const Solution& solution) override;
};

#endif // REINSERT_LOCAL_SEARCH_H