

#include <iostream>
#include <fstream>

#include "problem.h"

Problem::Problem(std::string filename) {
  std::ifstream inputFile(filename);
  if (!inputFile) {
    std::cerr << "Error: could not open file " << filename << std::endl;
    exit(1);
  }

  std::string currentLine;
  getline(inputFile, currentLine);
  currentLine.erase(0, 3);
  assignments_ = std::stoi(currentLine);
  getline(inputFile, currentLine);
  currentLine.erase(0, 3);
  machines_ = std::stoi(currentLine);
  getline(inputFile, currentLine);
  currentLine.erase(0, 11);
  // convertir la string en vector de ints
  std::string delimiter = "\t";
  size_t pos = 0;
  std::string token;
  while ((pos = currentLine.find(delimiter)) != std::string::npos) {
    token = currentLine.substr(0, currentLine.find(delimiter));
    assignmentsCosts_.push_back(std::stoi(token));
    currentLine = currentLine.substr(currentLine.find(delimiter) + 1);
  }
  assignmentsCosts_.push_back(std::stoi(currentLine));
  setupCosts_.resize(assignments_ + 1, std::vector<int>(assignments_ + 1));
  getline(inputFile, currentLine);
  int i = 0;
  while(getline(inputFile, currentLine) && i < assignments_) {
    std::string delimiter = "\t";
    size_t pos = 0;
    std::string token;
    int j = 0;
    while ((pos = currentLine.find(delimiter)) != std::string::npos) {
      token = currentLine.substr(0, currentLine.find(delimiter));
      setupCosts_[i][j] = std::stoi(token);
      currentLine = currentLine.substr(currentLine.find(delimiter) + 1);
      j++;
    }
    // setupCosts_[i][j] = std::stoi(currentLine);
    i++;
  }

  assigned_.resize(assignments_ + 1, false);
  inputFile.close();
}

bool Problem::IsAssigned(int assignment) {
  return assigned_[assignment];
}

bool Problem::HasUnassigned() const {
  for (int i = 1; i < assignments_; i++) {
    if (!assigned_[i]) {
      return true;
    }
  }
  return false;
}

void Problem::RestoreAssigned() {
  for (int i = 1; i < assignments_; i++) {
    assigned_[i] = false;
  }
}

  