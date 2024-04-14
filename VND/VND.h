#ifndef VND_H
#define VND_H

#include <vector>

#include "../problem/problem.h"
#include "../solution/solution.h"
#include "../GRASP-algorithm/GRASP-algorithm.h"
#include "../local-search/inter-reinsert-local-search/inter-reinsert-local-search.h"
#include "../local-search/swap-local-search/swap-local-search.h"
#include "../local-search/inter-swap-local-search/inter-swap-local-search.h"
#include "../local-search/reinsert-local-search/reinsert-local-search.h"


class VND {
 public:
  VND(const Problem problem) : problem_(problem) {}
  Solution ExecuteVND(Solution initialSolution);
 private:
  Problem problem_;
  Solution solution_;
  const int maxL = 4;
};

#endif  // VND_H