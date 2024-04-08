
#include <iostream>

#include "problem/problem.h"
#include "solution/solution.h"
#include "greedy-algorithm/greedy-algorithm.h"
#include "GRASP-algorithm/GRASP-algorithm.h"
#include "local-search/swap-local-search/swap-local-search.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }
  std::string filename = argv[1];
  Problem problem(filename);
  problem.CalculateTotalCosts();
  std::cout << "TotalCosts: " << std::endl;
  std::vector<std::vector<int>> totalCosts = problem.GetTotalCosts();
  for (int i = 0; i < totalCosts.size(); i++) {
    for (int j = 0; j < totalCosts[i].size(); j++) {
      std::cout << totalCosts[i][j] << " ";
    }
    std::cout << std::endl;
  }

  GreedyAlgorithm greedyAlgorithm(problem);
  Solution solution = greedyAlgorithm.Solve();
  std::cout << solution << std::endl;

  std::cout << "TCT: " << solution.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;

  // problem.RestoreAssigned();

  // const int kIterations = 10;

  GRASPAlgorithm graspAlgorithm(problem);
  Solution solution2 = graspAlgorithm.Solve();
  std::cout << solution2 << std::endl;
  std::cout << "TCT GRASP: " << solution2.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;

  // Busquedas locales
  SwapLocalSearch swapLocalSearch(problem, solution2);
  Solution solution3 = swapLocalSearch.Solve();
  std::cout << solution3 << std::endl;
  std::cout << "TCT BUSQUEDA LOCAL: " << solution3.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;



  return 0;
}