
#include <iostream>

#include "reinsert-local-search.h"

std::vector<Solution> ReinsertLocalSearch::GenerateNeighbors(const Solution& solution) {
  // reinsert an assignment in another position in the same sequence
  std::vector<Solution> neighbors;
  for (int i = 0; i < solution.GetAssignmentsSequences().size(); i++) {
    for (int j = 0; j < solution.GetAssignmentsSequences()[i].size(); j++) {
      for (int k = 0; k < solution.GetAssignmentsSequences()[i].size(); k++) {
        Solution neighbor = solution;
        neighbor.ReinsertAssignment(i, j, k);
        neighbors.push_back(neighbor);
      }
    }
  }
  return neighbors;
}