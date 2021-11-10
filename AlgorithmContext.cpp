#include "AlgorithmContext.h"
#include <chrono>

AlgorithmContext::AlgorithmContext(Algorithm *algo_,
                                   InputOutput<std::vector> &io_)
    : algo(algo_), io(io_) {}

AlgorithmContext::~AlgorithmContext() {
  delete this->algo;
  context_name = "";
}

void AlgorithmContext::set_algorithm(Algorithm *algo_,
                                     std::string &&context_name_) {
  delete this->algo;
  this->algo = algo_;
  context_name = context_name_;
}

void AlgorithmContext::run_algorithm() {
  const auto start = std::chrono::system_clock::now();
  this->algo->calculate_solution();
  const auto end = std::chrono::system_clock::now();
  const std::chrono::duration<double> diff = end - start;
  std::cout << "Time of running: " << diff.count() << " s\n";
  io.process_output_file(context_name, algo->get_solution(), diff.count());
}
