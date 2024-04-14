
#include "VND.h"


Solution VND::ExecuteVND(Solution initialSolution) {
  Solution bestSolution = initialSolution;
  int currentL = 1;
  do {
    // Explore the neighborhood.
    // std::cout << "Local search: " << currentL << std::endl;
    // std::cout << "TCT: " << bestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) << std::endl;
    switch (currentL) {
      problem_.RestoreAssigned();
      case 1: {
        InterReinsertLocalSearch interReinsertLocalSearch(problem_, bestSolution);
        solution_ = interReinsertLocalSearch.Solve();
        break;
      }
      case 2: {
        solution_ = SwapLocalSearch(problem_, bestSolution).Solve();
        break;
      }
      case 3: {
        solution_ = ReinsertLocalSearch(problem_, bestSolution).Solve();
        break;
      }
      case 4: {
        solution_ = InterSwapLocalSearch(problem_, bestSolution).Solve();
        break;
      }
    }
    // Move or not ?
    if (solution_.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts()) < bestSolution.calculatesTCT(problem_.GetTotalCosts(), problem_.GetAssignmentsCosts())) {
      bestSolution = solution_;
      currentL = 1;
      // std::cout << "se encontro mejor solucion" << std::endl;
    } else {
      currentL++;
      // std::cout << "no se encontro mejor solucion" << std::endl;
    }
  } while (currentL <= maxL);
  return solution_;
}