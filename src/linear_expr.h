#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "rational.h"
#include "sign.h"

namespace lqe {

  class linear_expr {
    std::vector<rational> coeffs;
    rational c;

  public:
    linear_expr(const int num_vars, const std::vector<rational>& p_coeffs) :
      coeffs(p_coeffs), c("0") {
      
    }

    linear_expr(const int num_vars,
		const std::vector<rational>& p_coeffs,
		const rational& p_c) :
      coeffs(p_coeffs), c(p_c) {
      
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

    int num_vars() const {
      return coeffs.size();
    }

    const rational& constant() const { return c; }

    bool equals(const linear_expr& r) const {
      assert(num_vars() == r.num_vars());

      if (c != r.c) {
	return false;
      }

      for (int i = 0; i < r.num_vars(); i++) {
	if (get_coeff(i) != r.get_coeff(i)) {
	  return false;
	}
      }

      return true;
    }
  };

  inline linear_expr operator+(const linear_expr& l, const linear_expr& r) {
    assert(l.num_vars() == r.num_vars());

    std::vector<rational> sum_coeffs;
    for (int i = 0; i < r.num_vars(); i++) {
      sum_coeffs.push_back(l.get_coeff(i) + r.get_coeff(i));
    }

    auto ct = l.constant() + r.constant();

    return linear_expr(l.num_vars(), sum_coeffs, ct);
  }

  inline bool operator==(const linear_expr& l, const linear_expr& r) {
    return l.equals(r);
  }

  std::ostream& operator<<(std::ostream& out, const linear_expr& expr);

}
