
#include <climits>
#include <iostream>

#include "greedy-algorithm.h"

/**
 * @brief Constructor de la clase GreedyAlgorithm.
 * @param problem Instancia del problema a resolver.
*/
Solution GreedyAlgorithm::Solve() {
  Solution solution(problem_.GetMachines());
  problem_.CalculateTotalCosts();
  std::vector<std::vector<int>> totalCosts = problem_.GetTotalCosts();
  // Seleccionar la m tareas m con menores valores de t0j para ser introducidas en las
  // primeras posiciones de los arrays que forman la solucion S.
  for (int i = 0; i < problem_.GetMachines(); i++) {
    int min = INT_MAX;
    int minIndex = -1;
    for (int j = 1; j < problem_.GetAssignments(); j++) {
      Solution auxSolution(solution);
      auxSolution.AddAssignment(i, j);
      int increment = auxSolution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts()) - 
      solution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts());
      if (increment < min && !problem_.IsAssigned(j)) {
        min = increment;
        minIndex = j;
      }
    }
    std::cout << "menor incremento del coste: " << min << " minIndex: " << minIndex << std::endl;
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
          Solution auxSolution(solution);
          auxSolution.AddAssignment(i, j);
          int increment = auxSolution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts()) -
          solution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts());
          if (increment < min) {
            min = increment;
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