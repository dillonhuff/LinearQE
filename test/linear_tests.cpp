#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "linear_expr.h"

namespace lqe {

  // Note add constructor that handles non-zero constant values in expressions
  TEST_CASE("Add linear expressions") {
    linear_expr a(2, {{"1"}, {"2"}});

    linear_expr b = a + a;

    linear_expr correct(2, {{"2"}, {"4"}});

    REQUIRE(b == correct);
  }

}
