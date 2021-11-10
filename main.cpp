#include <filesystem>
#include <vector>

#include "ACO.h"
#include "AlgorithmContext.h"
#include "Aprox.h"
#include "Graph.h"

int main() {
  const std::filesystem::path input_dir{"./input/"};

  for (const auto &file_path : std::filesystem::directory_iterator(input_dir)) {
    InputOutput<std::vector> io{file_path.path(), "./output/"};
    io.process_input_file();
    io.display_container();

    tsp::Graph<double, std::vector> graph{io};
    graph.display_graph();

    AlgorithmContext context{nullptr, io};

    context.set_algorithm(new Aprox(graph), "aprox_1");
    context.run_algorithm();
    context.set_algorithm(nullptr, "");

    context.set_algorithm(new ACO(graph), "aco_1");
    context.run_algorithm();
    context.set_algorithm(nullptr, "");
    graph.display_graph();
  }
  return 0;
}
