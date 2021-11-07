#include "Algo.h"

Algorithm::Algorithm(tsp::Graph<double, std::vector> &graph_)
    : graph{graph_}, randoms{}, solution(0) {
  std::cout << "New algorithm constructed" << std::endl;
}

Algorithm::~Algorithm() { std::cout << "Algorithm deconstructed" << std::endl; }