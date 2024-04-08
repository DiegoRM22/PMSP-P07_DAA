

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
