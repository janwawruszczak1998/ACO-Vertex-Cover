#include <vector>
#include <iostream>

#include "Graph.h"
#include "AlgorithmContext.h"
#include "ACO.h"


int main() {
    InputOutput<std::vector> io{std::move(std::string{"mvc.txt"})};
    io.process_file();
    io.display_container();

    tsp::Graph<double, std::vector> graph{std::move(io)};
    graph.display_graph();


    AlgorithmContext context{nullptr};
    context.set_algorithm(new ACO(graph));
    context.run_algorithm();
    context.set_algorithm(nullptr);
    graph.display_graph();

    return 0;
}
