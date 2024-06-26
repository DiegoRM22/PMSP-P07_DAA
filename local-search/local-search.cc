
#include <iostream>

#include "local-search.h"

/**
  * @brief Method to solve the problem.
  * @return The best solution found.
  */
Solution LocalSearch::Solve() {
  Solution bestSolution = currentSolution_;
  // print neighbor solutions
  std::vector<Solution> neighbors = GenerateNeighbors(currentSolution_);
  do {
    currentSolution_ = FindBestNeighbor(neighbors);
    
    if (currentSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < bestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      bestSolution = currentSolution_;
    }
    neighbors = GenerateNeighbors(currentSolution_);
  } while (!IsLocalOptimum(currentSolution_, neighbors));
  return bestSolution;
}

/**
 * @brief Generates a random solution.
 * @return Random solution.
 */
Solution LocalSearch::GenerateRandomSolution() {
  std::vector<Solution> neighbors = GenerateNeighbors(currentSolution_);
  return neighbors[rand() % neighbors.size()];
}
  

/**
 * @brief Finds the first better neighbor.
 * @param neighbors Neighbors to evaluate.
 * @return The first better neighbor.
 */
Solution LocalSearch::FindBetterNeighbor(const std::vector<Solution>& neighbors) {
  for (const Solution& neighbor : neighbors) {
    if (neighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < currentSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      return neighbor;
    }
  }
  return currentSolution_;
}

/**
 * @brief Finds the best neighbor.
 * @param neighbors Neighbors to evaluate.
 * @return The best neighbor.
 */
Solution LocalSearch::FindBestNeighbor(const std::vector<Solution>& neighbors) {
  Solution bestNeighbor = neighbors[0];
  for (const Solution& neighbor : neighbors) {
    if (neighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < bestNeighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      bestNeighbor = neighbor;
    }
  }
  return bestNeighbor;
}

/**
 * @brief Checks if the solution is a local optimum.
 * @param solution Solution to evaluate.
 * @param neighbors Neighbors to evaluate.
 * @return True if the solution is a local optimum, false otherwise.
 */
bool LocalSearch::IsLocalOptimum(const Solution& solution, const std::vector<Solution>& neighbors) {
  for (const Solution& neighbor : neighbors) {
    if (neighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < solution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      return false;
    }
  }
  return true;
}