#include <memory>

#include <iostream>

#include "catch.hpp"

#include "linear_expr.h"
#include "elimination.h"
#include "formula.h"
#include "sign_table.h"

using namespace std;

namespace lqe {

  TEST_CASE("x > 0 is satisfied") {
    linear_expr x(1, {{"1"}});

    sign_table st(0, {x}, {{0}});

    unique_ptr<formula> f = unique_ptr<formula>(new atom(GREATER, x));

    REQUIRE(is_sat_wrt_table(st, f.get()));
  }

  TEST_CASE("2x + y + 3 > 0 and 2x + y + 3 < 0 is not satisfied for any y") {
    linear_expr p(2, {{"2"}, {"1"}}, {"3"});

    sign_table st(1, {p}, {{0}});

    unique_ptr<formula> p_gtz = unique_ptr<formula>(new atom(GREATER, p));
    unique_ptr<formula> p_ltz = unique_ptr<formula>(new atom(LESS, p));
    unique_ptr<formula> f =
      unique_ptr<formula>(new conjunction({p_gtz.get(), p_ltz.get()}));

    REQUIRE(!is_sat_wrt_table(st, f.get()));
  }

  TEST_CASE("3x + 4y - 7 < 0 and 2x - y + 3 >= 0 is satisfied for some x") {
    linear_expr p(2, {{"3"}, {"4"}}, {"-7"});
    linear_expr q(2, {{"2"}, {"-1"}}, {"3"});

    sign_table st(1, {p, q}, {{1}, {0}});

    unique_ptr<formula> p_gtz = unique_ptr<formula>(new atom(LESS, p));
    unique_ptr<formula> p_leq = unique_ptr<formula>(new atom(GEQ, q));

    cout << "Less than intervals: " << endl;
    for (auto i : sat_intervals_wrt_table(st, *(p_gtz.get()))) {
      cout << i << ", ";
    }
    cout << endl;

    cout << "GEQ than intervals: " << endl;
    for (auto i : sat_intervals_wrt_table(st, *(p_leq.get()))) {
      cout << i << ", ";
    }
    cout << endl;
    
    unique_ptr<formula> f =
      unique_ptr<formula>(new conjunction({p_gtz.get(), p_leq.get()}));

    REQUIRE(is_sat_wrt_table(st, f.get()));
  }

}
