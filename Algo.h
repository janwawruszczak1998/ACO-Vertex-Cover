#ifndef AOIN_ALGO_H
#define AOIN_ALGO_H

#include <vector>
#include <thread>
#include <mutex>

#include "Graph.h"

class Algorithm{
public:
    Algorithm(tsp::Graph<>, std::vector&);
    virtual ~Algorithm();

    virtual void calvulate_solution() = 0;

    static bool run_flag;

protected:
    std::thread algo_thread{};
    std::mutex result_mutex{};
    std::vector<unsigned> solution;

};


#endif //AOIN_ALGO_H