
#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>

class Solution {
 public:
  Solution(const int machines) {
    assignmentsSequences_.resize(machines);
  }
  Solution(std::vector<std::vector<int>> assignmentsSequences) : assignmentsSequences_(assignmentsSequences) {}
  std::vector<std::vector<int>> GetAssignmentsSequences() const { return assignmentsSequences_; }
  void AddAssignment(int machine, int assignment) {
    assignmentsSequences_[machine].push_back(assignment);
  }
  int calculatesTCT(const std::vector<std::vector<int>>& totalCosts, const std::vector<int>& assigmentCosts) const;
  void SwapAssignments(int machine, int firstAssignment, int secondAssignment);
 private:
  std::vector<std::vector<int>> assignmentsSequences_;
};

std::ostream& operator<<(std::ostream& os, const Solution& solution);

#endif  // SOLUTION_H