
#include <iostream>

#include "inter-swap-local-search.h"

/**
 * @brief Generates the neighbors of a solution.
 * @param solution Solution to generate the neighbors.
 * @return Neighbors of the solution.
 */
std::vector<Solution> InterSwapLocalSearch::GenerateNeighbors(const Solution& solution) {
  // swap two assignments between two different sequences
  std::vector<Solution> neighbors;
  for (int i = 0; i < solution.GetAssignmentsSequences().size(); i++) {
    for (int j = 0; j < solution.GetAssignmentsSequences()[i].size(); j++) {
      for (int k = 0; k < solution.GetAssignmentsSequences().size(); k++) {
        for (int l = 0; l < solution.GetAssignmentsSequences()[k].size(); l++) {
          if (i == k) continue;
          Solution neighbor = solution;
          neighbor.InterchangeAssignments(i, j, k, l);
          neighbors.push_back(neighbor);
        }
      }
    }
  }
  return neighbors;
}