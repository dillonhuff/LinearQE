#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "linear_expr.h"

namespace lqe {

  TEST_CASE("Add linear expressions") {
    linear_expr a(2, {{"1"}, {"2"}});
  }

}
