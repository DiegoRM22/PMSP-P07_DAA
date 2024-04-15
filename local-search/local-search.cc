
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
    const Solution& original = currentSolution_;
    currentSolution_ = FindBestNeighbor(neighbors);
    if (!isInterMachineMethod_) {
      int changedMachine = FindChangedMachine(bestSolution, currentSolution_);
      currentSolution_.RecalculeTCTForMachine(changedMachine, problem_.GetTotalCosts(), problem_.GetAssignmentsCosts(), original);
      if (currentSolution_.GetTCT() < bestSolution.GetTCT()) {
        bestSolution = currentSolution_;
      }
    } else if (currentSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < bestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      bestSolution = currentSolution_;
    }
    neighbors = GenerateNeighbors(currentSolution_);
  } while (!IsLocalOptimum(currentSolution_, neighbors));
  return bestSolution;
}

/**
  * @brief Method to solve the problem.
  * @return The best solution found.
  */
Solution LocalSearch::SolveCopy() {
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
 * @brief Finds the machine that changed between two solutions.
 * @param solution Solution to compare.
 * @param neighbor Neighbor to compare.
 * @return The machine that changed.
 */
int LocalSearch::FindChangedMachine(const Solution& solution, const Solution& neighbor) {
  for (int i = 0; i < solution.GetAssignmentsSequences().size(); i++) {
    if (solution.GetAssignmentsSequences()[i] != neighbor.GetAssignmentsSequences()[i]) {
      return i;
    }
  }
  return -1;
}
  

/**
 * @brief Finds the first better neighbor.
 * @param neighbors Neighbors to evaluate.
 * @return The first better neighbor.
 */
Solution LocalSearch::FindBetterNeighbor(std::vector<Solution>& neighbors) {
  for (Solution& neighbor : neighbors) {
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
Solution LocalSearch::FindBestNeighbor(std::vector<Solution>& neighbors) {
  Solution bestNeighbor = neighbors[0];
  for (Solution& neighbor : neighbors) {
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
bool LocalSearch::IsLocalOptimum(Solution& solution, std::vector<Solution>& neighbors) {
  for (Solution& neighbor : neighbors) {
    if (neighbor.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < solution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      return false;
    }
  }
  return true;
}