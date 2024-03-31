

#include "solution.h"

#include <iostream>

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