#pragma once

#include "linear_expr.h"

namespace lqe {

  enum comparator { GREATER, LESS, EQUAL };

  enum fm_type { FM_ATOM, FM_CONJUNCTION, FM_DISJUNCTION, FM_NEGATION };

  class formula {
  public:
    virtual fm_type formula_type() const = 0;
  };

  class atom : public formula {
  public:
    atom(const comparator c, const linear_expr& lx) {
    }

    fm_type formula_type() const { return FM_ATOM; }
  };

  class conjunction : public formula {
  public:
    conjunction(const std::vector<formula*>& fms) {
    }

    fm_type formula_type() const { return FM_CONJUNCTION; }
  };
}
