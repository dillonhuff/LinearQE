#pragma once

#include "linear_expr.h"

namespace lqe {

  enum sign { POSITIVE, NEGATIVE, ZERO };

  class sign_table {
  protected:
    std::vector<sign> signs;
    int nrows, ncols;

  public:
    sign_table(const std::vector<linear_expr>& exprs,
	       const std::vector<std::vector<unsigned>>& order) {
      nrows = (order.size() - 1) + order.size() + 2;
      ncols = exprs.size();

      signs.resize(nrows*ncols);
    }

    int num_rows() const { return nrows; }

    int num_cols() const { return ncols; }
  };

}
