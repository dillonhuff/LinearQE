#pragma once

#include <vector>

namespace lqe {

  typedef std::vector<unsigned> equivalence_group;
  typedef std::vector<std::vector<unsigned> > order;

  std::vector<order> update_orders(const unsigned i, const order& order);

  std::vector<order> all_orders(const std::vector<unsigned>& values);

}
