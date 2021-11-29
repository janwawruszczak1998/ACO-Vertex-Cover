#include <filesystem>
#include <vector>

#include "ACO.h"
#include "AlgorithmContext.h"
#include "Aprox.h"
#include "Graph.h"
#include "TestsGenerator.h"

int main() {
// Uncomment only if test files need to be (re) generated
//TestsGenerator tg;
//tg.generate_tests();


  const std::filesystem::path input_dir{"./input/"};

  for (const auto &file_path : std::filesystem::directory_iterator(input_dir)) {
    InputOutput<std::vector> io{file_path.path(), "./output/"};
    io.process_input_file();

    tsp::Graph<double, std::vector> graph{io};

    AlgorithmContext context{nullptr, io};

    context.set_algorithm(new Aprox(graph), "aprox_1");
    context.run_algorithm();

    context.set_algorithm(new ACO(graph), "aco_1");
    context.run_algorithm();

  }
  return 0;
}
