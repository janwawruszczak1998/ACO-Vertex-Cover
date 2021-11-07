#include "Aprox.h"

Aprox::Aprox(tsp::Graph<double, std::vector> &graph_) : Algorithm(graph_) {
  std::cout << "New Aprox constructed" << std::endl;
}

Aprox::~Aprox() {
  std::cout << "2-approximate solution:\n";
  for (const auto vertex : solution) {
    std::cout << vertex << " ";
  }
  std::cout << std::endl;
  std::cout << "Aprox deconstructed" << std::endl;
}

void Aprox::calculate_solution() {
  const auto N = graph.get_order();
  const auto &G = graph.get_graph();

  std::vector<bool> vertex_included_in_solution(N, false);
  for (unsigned i = 0; i < N; ++i) {
    if (!vertex_included_in_solution[i]) {
      for (unsigned j = 0; j < N; ++j) {
        if (auto are_adjacent = G[i][j].first;
            are_adjacent && !vertex_included_in_solution[j]) {
          vertex_included_in_solution[i] = true;
          vertex_included_in_solution[j] = true;
          break;
        }
      }
    }
  }

  for (unsigned i = 0; i < N; i++) {
    if (vertex_included_in_solution[i]) {
      solution.push_back(i);
    }
  }
}