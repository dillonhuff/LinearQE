#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "linear_expr.h"

using namespace std;

namespace lqe {

  TEST_CASE("Add linear expressions") {
    linear_expr a(2, {{"1"}, {"2"}});

    linear_expr b = a + a;

    linear_expr correct(2, {{"2"}, {"4"}});

    REQUIRE(b == correct);
  }

}
