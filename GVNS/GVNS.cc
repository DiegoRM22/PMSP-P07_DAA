
#include "GVNS.h"

Solution GVNS::ExecuteGVNS() {
  VND vnd(problem_);
  bestSolution_ = GRASPAlgorithm(problem_).Solve();
  initialSolution_ = bestSolution_;
  int k = 1;
  do {
    // Shaking
    Solution new_solution = Shake(bestSolution_, k);
    // std::cout << "Perturbando la solucion" << std::endl;
    // std::cout << "Ahora es: " << new_solution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) << std::endl;

    // VND algorithm
    Solution vnd_solution = vnd.ExecuteVND(new_solution);
    // Move or not  ?
    if (vnd_solution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < bestSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      bestSolution_ = vnd_solution;
      k = 1;
      // std::cout << "Se encontro mejor solucion" << std::endl;
      // std::cout << "TCT: " << bestSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) << std::endl;
    } else {
      // std::cout << "No se encontro mejor solucion, aumentando entorno." << std::endl;
      k++;
    }
  } while (k <= kMax);
  return bestSolution_;
}

Solution GVNS::Shake(const Solution& solution, int k) {
  Solution new_solution = solution;
  // Shaking for the k neighborhood index.
  for (int i = 0; i < k; i++) {
    new_solution = InterReinsertLocalSearch(problem_, new_solution).GenerateRandomSolution();
  }
  return new_solution;
}

void GVNS::CalculatesImprovement() {
  std::cout << "Mejora: " << (initialSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) 
                - bestSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) * 100 / 
                initialSolution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) << "%" << std::endl;
}

Solution GVNS::MultiStartGVNS(int iterations) {
  int notImprovedIterations = 0;
  const int maxNotImprovedIterations = 200;
  Solution currentBestSolution = ExecuteGVNS();
  do {
    Solution new_solution = ExecuteGVNS();
    
    if (new_solution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < currentBestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      std::cout << "Se encontro mejor solucion" << std::endl;
      bestSolution_ = new_solution;
      currentBestSolution = bestSolution_;
    } else {
      notImprovedIterations++;
    }
    problem_.RestoreAssigned();
    iterations--;
    std::cout << "Iteraciones restantes: " << iterations << std::endl;	
    std::cout << "MEJOR TCT: " << currentBestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) << std::endl;
  } while (iterations > 0 && notImprovedIterations < maxNotImprovedIterations);
  return currentBestSolution;
}
