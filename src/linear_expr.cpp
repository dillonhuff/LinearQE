#include "linear_expr.h"

namespace lqe {

  std::ostream& operator<<(std::ostream& out, const linear_expr& expr) {
    for (int i = 0; i < expr.num_vars(); i++) {
      out << "x" + std::to_string(i) << " + ";
    }
    //out << expr.constant();
    return out;
  }

}
