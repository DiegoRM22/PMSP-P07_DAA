#ifndef GVNS_H
#define GVNS_H

#include <iostream>

#include "../VND/VND.h"

class GVNS{
 public:
  GVNS(const Problem problem) : problem_(problem) {}
  Solution ExecuteGVNS();
  Solution MultiStartGVNS(int iterations);
  Solution Shake(const Solution& solution, int k);
  void CalculatesImprovement();

 private:
  const int kMax = 6;
  Problem problem_;
  Solution initialSolution_;
  Solution bestSolution_;
};

#endif  // GVNS_H