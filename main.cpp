#include <vector>
#include <iostream>

#include "InputOutput.h"
#include "Graph.h"


int main() {
    InputOutput io{std::string{"mvc.txt"}};
    io.process_file();
    tsp::Graph<double, std::vector> graph{};
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
