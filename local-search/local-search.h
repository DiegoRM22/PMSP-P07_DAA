
#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <vector>

#include "../problem/problem.h"
#include "../solution/solution.h"

class LocalSearch {
 public:
  LocalSearch(Problem problem, Solution solution) : problem_(problem), currentSolution_(solution) {}
  Solution Solve();
  Solution SolveCopy();
  Solution GenerateRandomSolution();
  virtual std::vector<Solution> GenerateNeighbors(const Solution& solution) = 0;
  Solution FindBetterNeighbor(std::vector<Solution>& neighbors);
  Solution FindBestNeighbor(std::vector<Solution>& neighbors);
  bool IsLocalOptimum(Solution& solution, std::vector<Solution>& neighbors);
  int FindChangedMachine(const Solution& solution, const Solution& neighbor);
 protected:
  Solution currentSolution_;
  Problem problem_;
  bool isInterMachineMethod_ = false;
};

#endif // LOCAL_SEARCH_H