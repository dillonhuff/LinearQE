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
	linear_expr(1, {{"3"}})};
    vector<vector<unsigned> > order{{0}, {1}};
    
    sign_table t(exprs, order);

    SECTION("Has 5 rows") {
      REQUIRE(t.num_rows() == 5);
    }

    SECTION("Has 2 columns") {
      REQUIRE(t.num_cols() == 2);
    }
  }
  
  
}
