#ifndef AOIN_ACO_H
#define AOIN_ACO_H

#include "Algo.h"

class ACO : public Algo {
public:
    ~ACO();

    void calculate_solution() override;
};

#endif //AOIN_ACO_H