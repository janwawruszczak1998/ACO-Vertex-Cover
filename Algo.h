#ifndef AOIN_ALGO_H
#define AOIN_ALGO_H

#include <vector>
#include <thread>
#include <mutex>

#include "Graph.h"

class Algorithm{
public:
    Algorithm(tsp::Graph<double, std::vector>, std::vector<unsigned>&);
    virtual ~Algorithm();

    virtual void calculate_solution() = 0;

    static bool run_flag;

protected:
    std::thread algo_thread{};
    std::mutex result_mutex{};
    std::vector<unsigned> solution;

};


#endif //AOIN_ALGO_H