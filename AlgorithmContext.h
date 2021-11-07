#ifndef AOIN_ALGORITHMCONTEXT_H
#define AOIN_ALGORITHMCONTEXT_H

#include "Algo.h"

/**
The Context maintains a reference to one of the Strategy (Algo)
objects. The Context does not know the concrete class of a strategy. It
should work with all strategies via the Algo interface (pure virtual method).
*/
class AlgorithmContext {
public:
  explicit AlgorithmContext(Algorithm *);
  ~AlgorithmContext();

  /**
  Usually, the Context allows replacing a Strategy object at runtime.
  */
  void set_algorithm(Algorithm *);

  /**
  The Context delegates some work to the Strategy object instead of
  implementing +multiple versions of the algorithm on its own.
  Concrete Strategies implement the algorithm while following the base Strategy
  interface. The interface makes them interchangeable in the Context.
  */
  void run_algorithm();

private:
  Algorithm *algo;
};

#endif // AOIN_ALGORITHMCONTEXT_H