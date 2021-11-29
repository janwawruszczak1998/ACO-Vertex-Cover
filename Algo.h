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

  const std::vector<unsigned int> &get_solution() const;

  template <typename Container>
  double get_solution_value(const Container &solution_) {
    return static_cast<double>(solution_.size()) /
           static_cast<double>(solution.size());
  }

  template <typename Container>
  bool check_if_vertex_cover(const Container &solution_, unsigned& current_edges, const unsigned new_vertex) {
      std::set<unsigned> solution_vertices(solution_.begin(), solution_.end());
    unsigned edges_in_solution = current_edges;

    for(auto neighbour = 0u; neighbour < graph.get_order(); ++neighbour){
        if(graph.get_graph()[new_vertex][neighbour].first && !solution_vertices.contains(neighbour)){
            edges_in_solution++;
        }
    }

    current_edges = edges_in_solution;

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
