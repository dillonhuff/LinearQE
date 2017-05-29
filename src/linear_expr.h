#pragma once

#include <vector>

#include "rational.h"
#include "sign.h"

namespace lqe {

  class linear_expr {
    std::vector<rational> coeffs;

  public:
    linear_expr(const int num_vars, const std::vector<rational>& p_coeffs) :
      coeffs(p_coeffs) {
      
    }

    sign sign_at_infinity(const int variable) const {
      const rational& term = get_coeff(variable);
      int sg = term.sign();
      if (sg == 0) { return ZERO; }
      if (sg == 1) { return POSITIVE; }
      return NEGATIVE;

    }

    const rational& get_coeff(const int i) const {
      return coeffs[i];
    }

  };

  inline linear_expr operator+(const linear_expr& l, const linear_expr& r) {
    return l;
  }

  inline bool operator==(const linear_expr& l, const linear_expr& r) {
    return true;
  }


}
