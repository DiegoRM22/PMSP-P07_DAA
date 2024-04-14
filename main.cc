
#include <iostream>

#include "problem/problem.h"
#include "solution/solution.h"
#include "greedy-algorithm/greedy-algorithm.h"
#include "GRASP-algorithm/GRASP-algorithm.h"
#include "local-search/local-search.h"
#include "local-search/swap-local-search/swap-local-search.h"
#include "local-search/inter-swap-local-search/inter-swap-local-search.h"
#include "local-search/reinsert-local-search/reinsert-local-search.h"
#include "local-search/inter-reinsert-local-search/inter-reinsert-local-search.h"
#include "VND/VND.h"
#include "GVNS/GVNS.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }
  std::string filename = argv[1];
  Problem problem(filename);
  problem.CalculateTotalCosts();
  std::vector<std::vector<int>> totalCosts = problem.GetTotalCosts();

  GreedyAlgorithm greedyAlgorithm(problem);
  Solution solution = greedyAlgorithm.Solve();
  std::cout << "TCT GREEDY: " << solution.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  std::cout << solution << std::endl;

  problem.RestoreAssigned();

  GRASPAlgorithm graspAlgorithm(problem);
  Solution solution2 = graspAlgorithm.Solve();
  int graspTCT = solution2.calculatesTCT(totalCosts, problem.GetAssignmentsCosts());
  std::cout << "TCT GRASP: " << solution2.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  std::cout << solution2 << std::endl;

  // Busquedas locales
  // EVALUACION DE MOVIMIENTOS
  SwapLocalSearch swapLocalSearch(problem, solution2);
  Solution solution3 = swapLocalSearch.Solve();
  int swapTCT = solution3.calculatesTCT(totalCosts, problem.GetAssignmentsCosts());
  double improvement = (graspTCT - swapTCT) * 100 / graspTCT;
  std::cout << "TCT SWAP: " << swapTCT << std::endl;
  std::cout << "Porcentaje de mejora con respecto a GRASP: " << improvement << "%" << std::endl;
  std::cout << solution3 << std::endl;

  InterSwapLocalSearch interSwapLocalSearch(problem, solution2);
  Solution solution4 = interSwapLocalSearch.Solve();
  int interSwapTCT = solution4.calculatesTCT(totalCosts, problem.GetAssignmentsCosts());
  improvement = (graspTCT - interSwapTCT) * 100 / graspTCT;
  std::cout << "TCT SWAP INTER MAQUINA: " << solution4.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  std::cout << "Porcentaje de mejora con respecto a GRASP: " << improvement << "%" << std::endl;
  std::cout << solution4 << std::endl;

  ReinsertLocalSearch reinsertLocalSearch(problem, solution2);
  Solution solution5 = reinsertLocalSearch.Solve();
  int reinsertTCT = solution5.calculatesTCT(totalCosts, problem.GetAssignmentsCosts());
  improvement = (graspTCT - reinsertTCT) * 100 / graspTCT;
  std::cout << "TCT REINSERTAR BUSQUEDA LOCAL: " << solution5.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  std::cout << "Porcentaje de mejora con respecto a GRASP: " << improvement << "%" << std::endl;
  std::cout << solution5 << std::endl;

  InterReinsertLocalSearch interReinsertLocalSearch(problem, solution2);
  Solution solution6 = interReinsertLocalSearch.Solve();
  int interReinsertTCT = solution6.calculatesTCT(totalCosts, problem.GetAssignmentsCosts());
  improvement = (graspTCT - interReinsertTCT) * 100 / graspTCT;
  std::cout << "TCT REINSERTAR INTERMAQUINA BUSQUEDA LOCAL: " << solution6.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  std::cout << "Porcentaje de mejora con respecto a GRASP: " << improvement << "%" << std::endl;
  std::cout << solution6 << std::endl;


  std::cout << "VNS" << std::endl;
  // VND vnd(problem);
  // Solution solution7 = vnd.ExecuteVND();
  GVNS gvns(problem);
  // Solution solution7 = gvns.ExecuteGVNS();
  // improvement = (graspTCT - solution7.calculatesTCT(totalCosts, problem.GetAssignmentsCosts())) * 100 / graspTCT;
  // std::cout << "TCT GVNS: " << solution7.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  // gvns.CalculatesImprovement();
  // std::cout << solution7 << std::endl;
  Solution solution8 = gvns.MultiStartGVNS(10);
  std::cout << "TCT GVNS: " << solution8.calculatesTCT(totalCosts, problem.GetAssignmentsCosts()) << std::endl;
  gvns.CalculatesImprovement();
  std::cout << solution8 << std::endl;


  return 0;
}