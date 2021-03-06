#ifndef AOIN_ACO_H
#define AOIN_ACO_H

#include "Algo.h"
#include "Graph.h"
#include <memory>
#include <set>

class ACO : public Algorithm {
public:
  explicit ACO(tsp::Graph<double, std::vector> &);
  ~ACO() override;

  void calculate_solution() override;
  void update_pheromones(const std::vector<std::vector<unsigned>> &);

  class Ant {
  public:
    Ant(ACO &, unsigned, unsigned);
    ~Ant();

    [[nodiscard]] unsigned get_number() const;
    std::vector<unsigned> make_route();
    double Phi(unsigned, unsigned);
    unsigned edges_in_solution;
    unsigned get_next_city(const std::vector<double> &);

  private:
    const unsigned number;
    ACO &aco;
    std::vector<bool> vertex_tabu;
    std::vector<unsigned> route;
  };
};

#endif // AOIN_ACO_H