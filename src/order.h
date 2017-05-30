#pragma once

#include "linear_expr.h"

namespace lqe {

  typedef std::vector<std::vector<unsigned> > order;

  std::vector<order> update_orders(const unsigned i, const order& order);
}
