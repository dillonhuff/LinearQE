#pragma once

#include "linear_expr.h"

namespace lqe {

  enum comparator { GREATER, LESS, EQUAL, LEQ, GEQ };

  enum fm_type { FM_ATOM, FM_CONJUNCTION, FM_DISJUNCTION, FM_NEGATION };

  class formula {
  public:
    virtual fm_type formula_type() const = 0;
  };

  class atom : public formula {
  protected:
    comparator c;
    linear_expr lx;

  public:
    atom(const comparator p_c, const linear_expr& p_lx) : c(p_c), lx(p_lx) {}

    comparator predicate() const { return c; }

    const linear_expr& expr() const { return lx; }

    fm_type formula_type() const { return FM_ATOM; }
  };

  class conjunction : public formula {
  public:
    conjunction(const std::vector<formula*>& fms) {
    }

    fm_type formula_type() const { return FM_CONJUNCTION; }
  };
}
