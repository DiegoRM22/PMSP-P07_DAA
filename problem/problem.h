
#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>
#include <vector>

class Problem {
 public:
  Problem(std::string filename);
  ~Problem() = default;
  int GetAssignments() const { return assignments_; }
  int GetMachines() const { return machines_; }
  std::vector<int> GetAssignmentsCosts() const { return assignmentsCosts_; }
  std::vector<std::vector<int>> GetSetupCosts() const { return setupCosts_; }
  std::vector<bool> GetAssigned() const { return assigned_; }
  void SetAssigned(int assignment) { assigned_[assignment] = true; }
  bool IsAssigned(int assignment);
  bool HasUnassigned() const;
  void RestoreAssigned();
  std::vector<bool> assigned_;


 private:
  int assignments_;
  int machines_;
  std::vector<int> assignmentsCosts_;
  std::vector<std::vector<int>> setupCosts_;
};

#endif  // PROBLEM_H


