#include <random>
#include "Randoms.h"


using namespace re;


double Randoms::uniform() {
    std::uniform_real_distribution<> dist(0.1, 1);
    std::mt19937 engine(rand_device());
    return dist(engine);
}
