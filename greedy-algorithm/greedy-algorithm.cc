
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
    for (int j = 1; j < problem_.GetAssignments(); j++) {
      int t0j = problem_.GetSetupCosts()[0][j] + problem_.GetAssignmentsCosts()[j];
      if (t0j < min && !problem_.IsAssigned(j)) {
        min = t0j;
        minIndex = j;
      }
    }
    solution.AddAssignment(i, minIndex);
    problem_.SetAssigned(minIndex);
    TCT += min;
  }

  while(problem_.HasUnassigned()) {
    int min = INT_MAX;
    int minMachine = -1;
    int minAssignment = -1;
    for (int i = 0; i < problem_.GetMachines(); i++) {
      for (int j = 1; j < problem_.GetAssignments(); j++) {
        if (!problem_.IsAssigned(j)) {
          int tij = problem_.GetSetupCosts()[solution.GetAssignmentsSequences()[i].back()][j] + problem_.GetAssignmentsCosts()[j];
          if (tij < min) {
            min = tij;
            minMachine = i;
            minAssignment = j;
          }
        }
      }
    }
    solution.AddAssignment(minMachine, minAssignment);
    problem_.SetAssigned(minAssignment);
    TCT += min;
  }

  std::cout << "TCT: " << TCT << std::endl;
  return solution;
}