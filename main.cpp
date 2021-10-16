#include <vector>
#include <iostream>

#include "InputOutput.h"
#include "Graph.h"


int main() {
    InputOutput io{std::string{"mvc.txt"}};
    io.process_file();
    tsp::Graph<double, std::vector> graph{};
    graph.add_vertex();
    graph.add_vertex();
    graph.add_vertex();

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    graph.display_graph();
    return 0;
}
