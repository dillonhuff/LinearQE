#include "catch.hpp"

#include "sign_table.h"

using namespace std;

namespace lqe {

  TEST_CASE("Sign table with 1 non constant") {
    vector<linear_expr> exprs{linear_expr(1, {{"5"}})};
    vector<vector<unsigned> > order{{0}};
    
    sign_table t(exprs, order);

    SECTION("has 3 rows") {
      REQUIRE(t.num_rows() == 3);
    }

    SECTION("has 1 column") {
      REQUIRE(t.num_cols() == 1);
    }
  }

  TEST_CASE("Sign table with 2 non constant entries and different roots has 5 rows") {
    vector<linear_expr> exprs{linear_expr(1, {{"5"}}),
	linear_expr(1, {{"-3"}})};
    vector<vector<unsigned> > order{{0}, {1}};
    
    sign_table t(exprs, order);

    SECTION("Has 5 rows") {
      REQUIRE(t.num_rows() == 5);
    }

    SECTION("Has 2 columns") {
      REQUIRE(t.num_cols() == 2);
    }

    SECTION("Expression 2 has sign positive sign on interval 0") {
      REQUIRE(t.sign_on_interval(1, 0) == POSITIVE);
    }
  }

  TEST_CASE("Sign table with 3 non constant entries with the same roots") {
    vector<linear_expr> exprs{linear_expr(1, {{"5"}}),
	linear_expr(1, {{"3"}}),
	linear_expr(1, {{"-7"}})};
    vector<vector<unsigned> > order{{0, 1, 2}};
    
    sign_table t(exprs, order);

    SECTION("Has 3 rows") {
      REQUIRE(t.num_rows() == 3);
    }

    SECTION("Has 3 columns") {
      REQUIRE(t.num_cols() == 3);
    }

    SECTION("First expression has sign NEGATIVE on interval 0") {
      REQUIRE(t.sign_on_interval(0, 0) == NEGATIVE);
    }

    SECTION("First expression has sign Zero on interval 1") {
      REQUIRE(t.sign_on_interval(0, 1) == ZERO);
    }

    SECTION("First expression has sign Positive on interval 2") {
      REQUIRE(t.sign_on_interval(0, 2) == POSITIVE);
    }

    SECTION("Second expression has sign NEGATIVE on interval 0") {
      REQUIRE(t.sign_on_interval(1, 0) == NEGATIVE);
    }

    SECTION("Second expression has sign Zero on interval 1") {
      REQUIRE(t.sign_on_interval(1, 1) == ZERO);
    }

    SECTION("Second expression has sign Positive on interval 2") {
      REQUIRE(t.sign_on_interval(1, 2) == POSITIVE);
    }

    SECTION("Third expression has sign NEGATIVE on interval 0") {
      REQUIRE(t.sign_on_interval(2, 0) == NEGATIVE);
    }

    SECTION("Third expression has sign Zero on interval 1") {
      REQUIRE(t.sign_on_interval(2, 1) == ZERO);
    }

    SECTION("Third expression has sign Positive on interval 2") {
      REQUIRE(t.sign_on_interval(2, 2) == POSITIVE);
    }
    
  }
  
  
}
