#ifndef AOIN_ALGO_H
#define AOIN_ALGO_H

#include <set>
#include <vector>
//#include <thread>
#include <mutex>

#include "Graph.h"
#include "Randoms.h"

class Algorithm {
public:
  explicit Algorithm(tsp::Graph<double, std::vector> &);
  virtual ~Algorithm();

  virtual void calculate_solution() = 0;

  template <typename Container> double get_solution_value(const Container& solution_) {
    return static_cast<double>(solution_.size()) /
           static_cast<double>(solution.size());
  }

  template <typename Container>
  bool check_if_vertex_cover(const Container& solution_) {
    unsigned edges_in_solution = 0;
    std::vector<std::pair<unsigned, unsigned>> removed_pairs;
    for (const auto &vertex : solution_) {
      for (auto neighbour = 0u; neighbour < graph.get_order(); ++neighbour) {
        if (graph.get_graph()[vertex][neighbour].first == 1u) {
          edges_in_solution++;
          removed_pairs.push_back(std::make_pair(neighbour, vertex));
          graph.get_graph()[neighbour][vertex].first = false;
        }
      }
    }
    for (const auto &removed_pair : removed_pairs) {
      graph.get_graph()[removed_pair.first][removed_pair.second].first = true;
    }

    if (edges_in_solution == graph.get_size()) {
      return true;
    } else {
      return false;
    }
  }

protected:
  tsp::Graph<double, std::vector> &graph;
  std::vector<unsigned> solution;
  re::Randoms randoms;
};

#endif // AOIN_ALGO_H
