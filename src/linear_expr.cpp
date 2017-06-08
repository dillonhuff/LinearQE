#include "linear_expr.h"

using namespace std;

namespace lqe {

  std::ostream& operator<<(std::ostream& out, const linear_expr& expr) {
    for (int i = 0; i < expr.num_vars(); i++) {
      out << "(" << expr.get_coeff(i) << " * x" + std::to_string(i) << ") + ";
    }
    out << expr.constant();
    return out;
  }

  linear_expr linear_expr::symbolic_root(const int i) const {
    assert(num_vars() > 0);

    rational k = constant();
    rational x_c = get_coeff(i);
    rational new_c = -k / x_c;

    vector<rational> var_values;
    for (int j = 0; j < num_vars(); j++) {
      if (j == i) {
	var_values.push_back({"0"});
      } else {
	var_values.push_back({"0"});
      }
    }

    assert(var_values.size() == num_vars());
    
    return linear_expr(num_vars(), var_values, new_c);
  }

}
