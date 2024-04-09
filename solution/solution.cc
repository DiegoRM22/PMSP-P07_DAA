

#include "solution.h"

#include <iostream>

/**
 * @brief Operador de salida de la clase Solution.
 * @param os Stream de salida.
 * @param solution Solucion a imprimir.
 * @return Stream de salida.
*/
std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  for (int i = 0; i < solution.GetAssignmentsSequences().size(); i++) {
    os << "Machine " << i << ": ";
    for (int j = 0; j < solution.GetAssignmentsSequences()[i].size(); j++) {
      os << solution.GetAssignmentsSequences()[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}

/**
  * @brief Calculates the TCT
  * @return TCT
  */
int Solution::calculatesTCT(const std::vector<std::vector<int>>& totalCosts, const std::vector<int>& assigmentCosts) const {
  int TCT = 0;
  // Recorre las maquinas
  for (int r = 0; r < assignmentsSequences_.size(); r++) {
    int machineSize = assignmentsSequences_[r].size();
    for (int i = 0; i < machineSize; i++) {
      if ((i - 1) < 0) {
        // std::cout << "i: " << i << " r: " << r << " = " << 
        // (machineSize - i) << "*" << assigmentCosts[assignmentsSequences_[r][i] - 1] << std::endl;
        TCT += (machineSize - i) * assigmentCosts[assignmentsSequences_[r][i] - 1];

      } else {
        // std::cout << "i: " << i << " r: " << r << " = " <<
        // (machineSize - i) << "*" << totalCosts[assignmentsSequences_[r][i - 1] - 1][assignmentsSequences_[r][i] - 1] << std::endl;
        TCT += (machineSize - i) * totalCosts[assignmentsSequences_[r][i - 1] - 1][assignmentsSequences_[r][i] - 1];
      }
    }
  }
  return TCT;
}

/**
 * @brief Swaps two assignments in a machine.
 * @param machine Machine where the assignments are.
 * @param firstAssignment First assignment to swap.
 * @param secondAssignment Second assignment to swap.
*/
void Solution::SwapAssignments(int machine, int firstAssignment, int secondAssignment) {
  std::swap(assignmentsSequences_[machine][firstAssignment], assignmentsSequences_[machine][secondAssignment]);
}

/**
 * @brief Interchanges two assignments between two machines.
 * @param firstMachine Machine where the first assignment is.
 * @param firstAssignment First assignment to interchange.
 * @param secondMachine Machine where the second assignment is.
 * @param secondAssignment Second assignment to interchange.
*/
void Solution::InterchangeAssignments(int firstMachine, int firstAssignment, int secondMachine, int secondAssignment) {
  std::swap(assignmentsSequences_[firstMachine][firstAssignment], assignmentsSequences_[secondMachine][secondAssignment]);
}

/**
 * @brief Reinserts an assignment in another position in the same sequence.
 * @param machine Machine where the assignment is.
 * @param assignment Assignment to reinsert.
 * @param position Position to reinsert the assignment.
*/
void Solution::ReinsertAssignment(int machine, int assignment, int position) {
  int value = assignmentsSequences_[machine][assignment];
  assignmentsSequences_[machine].erase(assignmentsSequences_[machine].begin() + assignment);
  assignmentsSequences_[machine].insert(assignmentsSequences_[machine].begin() + position, value);
}

/**
 * @brief Reinserts an assignment in another position of another machine.
 * @param firstMachine Machine where the first assignment is.
 * @param firstAssignment First assignment to reinsert.
 * @param secondMachine Machine where the second assignment is.
 * @param secondAssignment Second assignment to reinsert.
*/
void Solution::ReinsertAssignment(int firstMachine, int firstAssignment, int secondMachine, int position) {
  int value = assignmentsSequences_[firstMachine][firstAssignment];
  assignmentsSequences_[firstMachine].erase(assignmentsSequences_[firstMachine].begin() + firstAssignment);
  assignmentsSequences_[secondMachine].insert(assignmentsSequences_[secondMachine].begin() + position, value);
}
