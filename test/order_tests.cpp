#include "catch.hpp"

#include "order.h"

using namespace std;

namespace lqe {

  TEST_CASE("Orders of objects") {
    vector<order> orders = update_orders(1, {{0}});

    REQUIRE(orders.size() == 3);
  }

}
