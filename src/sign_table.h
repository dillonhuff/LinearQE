#pragma once

#include <cassert>
#include <numeric>

#include "linear_expr.h"

namespace lqe {

  class sign_table {
  protected:
    std::vector<sign> signs;
    std::vector<linear_expr> column_labels;
    int nrows, ncols;

  public:
    sign_table(const int variable,
	       const std::vector<linear_expr>& exprs,
	       const std::vector<std::vector<unsigned>>& order) :
      column_labels(exprs) {
      nrows = (order.size() - 1) + order.size() + 2;
      ncols = exprs.size();

      signs.resize(nrows*ncols);

      for (int interval_index = 0; interval_index < order.size(); interval_index++) {
	std::vector<unsigned> polys_with_root_at_interval =
	  order[interval_index];

	for (auto poly_index : polys_with_root_at_interval) {
	  int root_interval_index = 2*interval_index + 1;

	  sign sign_at_inf = exprs[poly_index].sign_at_infinity(variable);
	  sign sign_at_ninf = flip(sign_at_inf);

	  // Set the point interval corresponding to the zero
	  // of this expression to zero
	  set_sign(poly_index, root_interval_index, ZERO);

	  // Set all intervals before the zero
	  // NOTE: Actually need to check derivative!!!
	  for (int row_index = 0; row_index < root_interval_index; row_index ++) {
	    set_sign(poly_index, row_index, sign_at_ninf);
	  }

	  // Set all intervals after it to be positive
	  for (int row_index = root_interval_index + 1;
	       row_index < num_rows(); row_index ++) {
	    set_sign(poly_index, row_index, sign_at_inf);
	  }
	  
	}
      }
    }

    int column_of(const linear_expr& l) const {
      for (int i = 0; i < column_labels.size(); i++) {
	if (column_labels[i] == l) {
	  return i;
	}
      }

      assert(false);
    }

    void set_sign(const int expr_index, const int interval_index, const sign sg) {
      signs[expr_index*num_rows() + interval_index] = sg;
    }

    int num_rows() const { return nrows; }

    int num_cols() const { return ncols; }

    sign sign_on_interval(const int expr_index, const int interval_index) const {
      return signs[expr_index*num_rows() + interval_index];
    }

    std::vector<int> all_intervals() const {
      std::vector<int> len(num_rows());
      std::iota(begin(len), end(len), 1);
      return len;
    }

  };

}
