#pragma once

#include "linear_expr.h"

namespace lqe {

  enum comparator {GREATER, LESS, EQUAL};

  class formula {
  };

  class atom : public formula {
  public:
    atom(const comparator c, const linear_expr& lx) {
    }
  };
}
