
#include <iostream>

#include "problem/problem.h"
#include "solution/solution.h"
#include "greedy-algorithm/greedy-algorithm.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }
  std::string filename = argv[1];
  Problem problem(filename);

  GreedyAlgorithm greedyAlgorithm(problem);
  Solution solution = greedyAlgorithm.Solve();
  std::cout << solution << std::endl;
  

  return 0;
}