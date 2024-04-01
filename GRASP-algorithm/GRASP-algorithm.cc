
#include <iostream>
#include <climits>

#include "GRASP-algorithm.h"

bool allVisited(std::vector<bool> visited) {
  for (int i = 0; i < visited.size(); i++) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

int getNumberOfVisited(std::vector<bool> visited) {
  int count = 0;
  for (int i = 0; i < visited.size(); i++) {
    if (visited[i]) {
      count++;
    }
  }
  return count;
}

Solution GRASPAlgorithm::Solve() {
  Solution solution(problem_.GetMachines());
  problem_.SetAssigned(0);
  problem_.assigned_.erase(problem_.assigned_.end());
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
        if (bestAssignments[randomIndex] != 0) {
          solution.AddAssignment(i, bestAssignments[randomIndex]);
        } else {
          bestAssignments.erase(bestAssignments.begin() + randomIndex);
        }
        problem_.SetAssigned(bestAssignments[randomIndex]);
        TCT += problem_.GetSetupCosts()[solution.GetAssignmentsSequences()[i].back()][bestAssignments[randomIndex]] + 
              problem_.GetAssignmentsCosts()[bestAssignments[randomIndex]];
        bestAssignments.erase(bestAssignments.begin() + randomIndex);
      }
    }
    
    if (problem_.GetAssignments() - getNumberOfVisited(problem_.assigned_) < problem_.GetMachines()) {
      for (int i = 1; i < problem_.GetAssignments(); i++) {
        if (!problem_.IsAssigned(i)) {
          solution.AddAssignment(0, i);
          problem_.SetAssigned(i);
          TCT += problem_.GetSetupCosts()[solution.GetAssignmentsSequences()[0].back()][i] + 
                problem_.GetAssignmentsCosts()[i];
        }
      }
    }
  }
  return solution;
}



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




