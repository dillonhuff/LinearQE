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

  TEST_CASE("Compute root with respect to a variable") {
    linear_expr a(1, {{"1"}}, {"-3"});
    linear_expr c = a.symbolic_root(0);
    linear_expr correct(1, {{"0"}}, {"3"});

    REQUIRE(c == correct);
  }

}
