
#include <iostream>

#include "swap-local-search.h"

// Solution SwapLocalSearch::Solve() {
//   Solution bestSolution = currentSolution_;
//   // print neighbor solutions
//   std::vector<Solution> neighbors = GenerateNeighbors(currentSolution_);
//   do {
//     currentSolution_ = FindBetterNeighbor(neighbors);
//     if (currentSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < bestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
//       bestSolution = currentSolution_;
//     }
//     neighbors = GenerateNeighbors(currentSolution_);
//   } while (!IsLocalOptimum(currentSolution_, neighbors));
//   return bestSolution;
// }

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

/**
 * @brief Finds the first better neighbor.
 * @param neighbors Neighbors to evaluate.
 * @return The first better neighbor.
 */
// Solution SwapLocalSearch::FindBetterNeighbor(const std::vector<Solution>& neighbors) {
//   for (const Solution& neighbor : neighbors) {
//     if (neighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < currentSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
//       return neighbor;
//     }
//   }
//   return currentSolution_;
// }

/**
 * @brief Checks if the solution is a local optimum.
 * @param solution Solution to evaluate.
 * @param neighbors Neighbors to evaluate.
 * @return True if the solution is a local optimum, false otherwise.
 */
// bool SwapLocalSearch::IsLocalOptimum(const Solution& solution, const std::vector<Solution>& neighbors) {
//   for (const Solution& neighbor : neighbors) {
//     if (neighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < solution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
//       return false;
//     }
//   }
//   return true;
// }