
#include <climits>
#include <iostream>

#include "greedy-algorithm.h"

Solution GreedyAlgorithm::Solve() {
  Solution solution(problem_.GetMachines());
  // Seleccionar la m tareas m con menores valores de t0j para ser introducidas en las
  // primeras posiciones de los arrays que forman la solucion S.
  for (int i = 0; i < problem_.GetMachines(); i++) {
    int min = INT_MAX;
    int minIndex = -1;
    std::cout << "machine " << i << std::endl;
    for (int j = 1; j < problem_.GetAssignments(); j++) {
      std::cout << "assignment " << j << std::endl;
      int t0j = problem_.GetSetupCosts()[0][j] + problem_.GetAssignmentsCosts()[j];
      std::cout << "t0j: " << t0j << std::endl;
      if (t0j < min && !problem_.IsAssigned(j)) {
        min = t0j;
        minIndex = j;
      }
    }
    solution.AddAssignment(i, minIndex);
    problem_.SetAssigned(minIndex);
  }

  return solution;
}