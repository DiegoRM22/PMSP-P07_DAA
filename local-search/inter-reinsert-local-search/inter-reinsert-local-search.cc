
#include <iostream>

#include "inter-reinsert-local-search.h"

/**
 * @brief Generates the neighbors of a solution.
 * @param solution Solution to generate the neighbors.
 * @return Neighbors of the solution.
 */
std::vector<Solution> InterReinsertLocalSearch::GenerateNeighbors(const Solution& solution) {
  // reinsert an assignment in another position of another machine
  std::vector<Solution> neighbors;
  for (int i = 0; i < solution.GetAssignmentsSequences().size(); i++) {
    for (int j = 0; j < solution.GetAssignmentsSequences()[i].size(); j++) {
      for (int k = 0; k < solution.GetAssignmentsSequences().size(); k++) {
        for (int l = 0; l < solution.GetAssignmentsSequences()[k].size(); l++) {
          if (i == k) continue; // skip if the machines are the same
          Solution neighbor = solution;
          neighbor.ReinsertAssignment(i, j, k, l);
          neighbors.push_back(neighbor);
        }
      }
    }
  }
  return neighbors;
}