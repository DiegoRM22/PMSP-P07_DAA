

#include <iostream>
#include <fstream>

#include "problem.h"

/**
 * @brief Constructor de la clase Problem.
 * @param filename Nombre del fichero con la instancia del problema.
*/
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
  setupCosts_.resize(assignments_, std::vector<int>(assignments_));
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

/**
 * @brief Devuelve el número de tareas.
 * @return Número de tareas.
*/
bool Problem::IsAssigned(int assignment) {
  return assigned_[assignment];
}

/**
 * @brief Devuelve el número de tareas.
 * @return Número de tareas.
*/
bool Problem::HasUnassigned() const {
  for (int i = 1; i < assignments_; i++) {
    if (!assigned_[i]) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Devuelve el número de tareas.
 * @return Número de tareas.
*/
void Problem::RestoreAssigned() {
  for (int i = 1; i < assignments_; i++) {
    assigned_[i] = false;
  }
}

/**
 * @brief Calcula los costes totales de las tareas.
*/
void Problem::CalculateTotalCosts() {
  totalCosts_.resize(assignments_, std::vector<int>(assignments_));
  for (int i = 0; i < assignments_; i++) {
    for (int j = 0; j < assignments_; j++) {
      totalCosts_[i][j] = setupCosts_[i][j] + assignmentsCosts_[j];
    }
  }
}

  