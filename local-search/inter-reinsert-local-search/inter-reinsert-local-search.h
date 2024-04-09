
#ifndef INTER_REINSERT_LOCAL_SEARCH_H
#define INTER_REINSERT_LOCAL_SEARCH_H

#include <vector>

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "../local-search.h"

class InterReinsertLocalSearch : public LocalSearch {
 public:
  InterReinsertLocalSearch(Problem problem, Solution solution) : LocalSearch(problem, solution) {}
  std::vector<Solution> GenerateNeighbors(const Solution& solution) override;
};

#endif // INTER_REINSERT_LOCAL_SEARCH_H