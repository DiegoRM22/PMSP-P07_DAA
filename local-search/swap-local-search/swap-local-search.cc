
#include <iostream>

#include "swap-local-search.h"

/**
 * @brief Generates the neighbors of a solution.
 * @param solution Solution to generate the neighbors.
 * @return Neighbors of the solution.
 */
std::vector<Solution> SwapLocalSearch::GenerateNeighbors(const Solution& solution) {
  std::vector<Solution> neighbors;
  for (int i = 0; i < solution.GetAssignmentsSequences().size(); i++) {
    for (int j = 0; j < solution.GetAssignmentsSequences()[i].size(); j++) {
      for (int k = j + 1; k < solution.GetAssignmentsSequences()[i].size(); k++) {
        Solution neighbor = solution;
        neighbor.SwapAssignments(i, j, k);
        neighbors.push_back(neighbor);
      }
    }
  }
  return neighbors;
}