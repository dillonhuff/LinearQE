#pragma once

#include <vector>

#include "rational.h"

namespace lqe {

  class linear_expr {
  public:
    linear_expr(const int num_vars, const std::vector<rational>& coeffs) {
      
    }
  };

  inline linear_expr operator+(const linear_expr& l, const linear_expr& r) {
    return l;
  }

  inline bool operator==(const linear_expr& l, const linear_expr& r) {
    return true;
  }


}
