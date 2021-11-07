#include "AlgorithmContext.h"
#include <chrono>

AlgorithmContext::AlgorithmContext(Algorithm* algo_ = nullptr) : algo(algo_) {
}

AlgorithmContext::~AlgorithmContext() {
    delete this->algo;
}

void AlgorithmContext::set_algorithm(Algorithm* algo_){
    delete this->algo;
    this->algo = algo_;
}

void AlgorithmContext::run_algorithm() {
    const auto start = std::chrono::system_clock::now();
    this->algo->calculate_solution();
    const auto end = std::chrono::system_clock::now();
    const std::chrono::duration<double> diff = end - start;
    std::cout << "Time of running: "  << diff.count() << " s\n";
}
