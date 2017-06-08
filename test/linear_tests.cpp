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

  TEST_CASE("Compute root with in one variable") {
    linear_expr a(1, {{"1"}}, {"-3"});
    linear_expr c = a.symbolic_root(0);
    linear_expr correct(1, {{"0"}}, {"3"});

    REQUIRE(c == correct);
  }

  TEST_CASE("Compute root with multiple variables") {
    linear_expr a(3, {{"2"}, {"9"}, {"-3"}}, {"2"});
    linear_expr c = a.symbolic_root(1);
    linear_expr correct(3, {{"-2/9"}, {"0"}, {"1/3"}}, {"-2/9"});

    REQUIRE(c == correct);
  }

}
