#include "AlgorithmContext.h"


AlgorithmContext::AlgorithmContext(Algorithm* algo_ = nullptr) : algo(algo_) {
}

AlgorithmContext::~AlgorithmContext() {
    delete this->algo;
}

void AlgorithmContext::set_algorithm(Algorithm* algo_){
    delete this->algo;
    this->algo = algo_;
}