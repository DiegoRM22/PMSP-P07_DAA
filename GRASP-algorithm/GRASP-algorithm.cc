
#include <iostream>
#include <climits>

#include "GRASP-algorithm.h"

/**
 * @brief Constructor de la clase GRASPAlgorithm.
 * @param problem Instancia del problema a resolver.
 * @param alpha Parametro de la heuristica.
*/
bool allVisited(std::vector<bool> visited) {
  for (int i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Constructor de la clase GRASPAlgorithm.
 * @param problem Instancia del problema a resolver.
 * @param alpha Parametro de la heuristica.
*/
int getNumberOfVisited(std::vector<bool> visited) {
  int count = 0;
  for (int i = 0; i < visited.size(); i++) {
    if (visited[i]) {
      count++;
    }
  }
  return count;
}

/**
 * @brief Constructor de la clase GRASPAlgorithm.
 * @param problem Instancia del problema a resolver.
 * @param alpha Parametro de la heuristica.
*/
Solution GRASPAlgorithm::Solve() {
  Solution solution(problem_.GetMachines());
  problem_.SetAssigned(0);
  problem_.assigned_.erase(problem_.assigned_.end());
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
    solution.AddAssignment(i, minIndex);
    problem_.SetAssigned(minIndex);
    TCT += min;
  }

  while(problem_.HasUnassigned()) {
    // Calculates the heuristic for each unassigned task.
    std::vector<int> heuristics;
    for (int i = 0; i < problem_.GetAssignments(); i++) {
      if (!problem_.IsAssigned(i)) {
        heuristics.push_back(CalculatesHeuristic(solution, i));
      }
    }
    // Creates a new vector with unassigned tasks.
    std::vector<int> unassignedAssignments;
    for (int i = 1; i < problem_.GetAssignments(); i++) {
      if (!problem_.IsAssigned(i)) {
        unassignedAssignments.push_back(i);
      }
    }
    // Creates a vector with the best tasks.
    std::vector<int> bestAssignments;
    while (bestAssignments.size() < problem_.GetMachines()) {
      int min = INT_MAX;
      int minIndex = -1;
      for (int i = 0; i < heuristics.size(); i++) {
        if (heuristics[i] == -1) {
          continue;
        }
        if (heuristics[i] < min) {
          min = heuristics[i];
          minIndex = i;
        }
      }
      bestAssignments.push_back(unassignedAssignments[minIndex]);
      heuristics[minIndex] = -1;
    }
    // For each machine, adds a random task from the best tasks.
    for (int i = 0; i < problem_.GetMachines(); i++) {
      if (bestAssignments.size() != 0) {
        int randomIndex = rand() % bestAssignments.size();
        Solution auxSolution(solution);
        if (bestAssignments[randomIndex] != 0) {
          solution.AddAssignment(i, bestAssignments[randomIndex]);
          TCT += solution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts()) -
          auxSolution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts());
        } else {
          bestAssignments.erase(bestAssignments.begin() + randomIndex);
        }
        problem_.SetAssigned(bestAssignments[randomIndex]);
        bestAssignments.erase(bestAssignments.begin() + randomIndex);
      }
    }
    if (problem_.GetAssignments() - getNumberOfVisited(problem_.assigned_) < problem_.GetMachines()) {
      for (int i = 1; i < problem_.GetAssignments(); i++) {
        if (!problem_.IsAssigned(i)) {
          Solution auxSolution(solution);
          solution.AddAssignment(0, i);
          problem_.SetAssigned(i);
          TCT += solution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts()) -
          auxSolution.calculatesTCT(totalCosts, problem_.GetAssignmentsCosts());
        }
      }
    }
  }
  return solution;
}

/**
 * @brief Ejecuta el algoritmo N veces.
 * @return Mejor solucion encontrada.
*/
Solution GRASPAlgorithm::executesNTimes(int iterations) {
  Solution bestSolution(problem_.GetMachines());
  int bestTCT = INT_MAX;
  for (int i = 0; i < iterations; i++) {
    Solution solution = Solve();
    if (TCT < bestTCT) {
      bestTCT = TCT;
      bestSolution = solution;
    }
    TCT = 0;
    problem_.RestoreAssigned();
  }
  return bestSolution;
}

/**
 * @brief Calcula la heuristica de una tarea.
 * @param solution Solucion actual.
 * @param assignment Tarea a la que se le va a calcular la heuristica.
 * @return Heuristica de la tarea.
*/
int GRASPAlgorithm::CalculatesHeuristic(const Solution& solution, int assignment) {
  int heuristic = 0;
  std::vector<bool> assignedAuxiliar = problem_.GetAssigned();
  //assignedAuxiliar.erase(assignedAuxiliar.end());
  
  while (!allVisited(assignedAuxiliar)) {
    assignedAuxiliar[assignment] = true;
    int min = INT_MAX;
    int nextAssignment = -1;
    for (int j = 1; j < problem_.GetAssignments(); j++) {
      if (!assignedAuxiliar[j]) {
        int tij = problem_.GetSetupCosts()[assignment][j];
        if (tij < min) {
          min = tij;
          nextAssignment = j;
        }
      }
    }
    if (nextAssignment == -1) {
      break;
    }
    heuristic += min;
    assignment = nextAssignment;
  }
  return heuristic;
}




