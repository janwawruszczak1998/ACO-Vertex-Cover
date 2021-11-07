#ifndef AOIN_APROX_H
#define AOIN_APROX_H

#include "Algo.h"

class Aprox : public Algorithm {
public:
  ~Aprox();

  void calculate_solution() override;
};

#endif // AOIN_Aprox_H