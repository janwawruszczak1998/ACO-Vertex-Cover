#include <vector>
#include <iostream>

#include "Graph.h"


int main() {
    InputOutput<std::vector> io{std::string{"mvc.txt"}};
    io.process_file();
    io.display_container();
    tsp::Graph<double, std::vector> graph{std::move(io)};

    graph.display_graph();
    return 0;
}
