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

    // cout << "Less than intervals: " << endl;
    // for (auto i : sat_intervals_wrt_table(st, *(p_gtz.get()))) {
    //   cout << i << ", ";
    // }
    // cout << endl;

    // cout << "GEQ than intervals: " << endl;
    // for (auto i : sat_intervals_wrt_table(st, *(p_leq.get()))) {
    //   cout << i << ", ";
    // }
    // cout << endl;
    
    unique_ptr<formula> f =
      unique_ptr<formula>(new conjunction({p_gtz.get(), p_leq.get()}));

    REQUIRE(is_sat_wrt_table(st, f.get()));
  }
  
  TEST_CASE("(3x + 4y + 2 = 0 and 3x + 4y + 7 < 0) or (-2x + 0y - 2 = 0)") {
    linear_expr p1(2, {{"3"}, {"4"}}, {"2"});
    linear_expr p2(2, {{"3"}, {"4"}}, {"7"});
    linear_expr p3(2, {{"-2"}, {"0"}}, {"-2"});

    auto p1_eq = mk_atom(EQUAL, p1);
    auto p2_lt = mk_atom(LESS, p2);
    auto p3_lt = mk_atom(EQUAL, p3);

    auto conj = mk_conjunction({p1_eq.get(), p2_lt.get()});
    auto fm = mk_disjunction({conj.get(), p3_lt.get()});

    SECTION("Can be satisifed along x") {
      sign_table st(0, {p1, p2, p3}, {{0}, {1}, {2}});

      REQUIRE(is_sat_wrt_table(st, fm.get()));
    }

    SECTION("Decides to true") {
      unique_ptr<formula> result = project_formula({0, 1}, *(fm.get()));

      REQUIRE(result->formula_type() == FM_TRUE);
    }
  }

  TEST_CASE("3x + 4y - 7 < 0 and 2x - y + 3 >= 0") {
    linear_expr p(2, {{"3"}, {"4"}}, {"-7"});
    linear_expr q(2, {{"2"}, {"-1"}}, {"3"});

    unique_ptr<formula> p_gtz = mk_atom(LESS, p);
    unique_ptr<formula> p_leq = mk_atom(GEQ, q);

    unique_ptr<formula> f = mk_conjunction({p_gtz.get(), p_leq.get()});

    SECTION("Is possibly true under partial set {p}") {
      cout << "Starting partial test" << endl;
      vector<linear_expr> sub{p};
      sign_table st(0, sub, {{0}});

      REQUIRE(is_sat_wrt_table(st, f.get()));
    }

    // for (auto ord : viable_orders) {
    //   print_order(ord);
    // }

    SECTION("Has one viable order") {
      vector<order> viable_orders =
	all_viable_orders(0, {p, q}, *f);


      REQUIRE(viable_orders.size() == 1);
    }
  }

  rational random_rational() {
    int value = rand() % 1000 - 500;
    return rational(std::to_string(value));
  }

  linear_expr random_linear_expression(const int num_variables) {
    vector<rational> coeffs;

    for (int i = 0; i < num_variables; i++) {
      coeffs.push_back(random_rational());
    }

    rational c = random_rational();

    return linear_expr(num_variables, coeffs, c);
  }

  // TEST_CASE("Stress test with twenty linear equations in 15 variables") {
  //   int variable = 4;
  //   int num_equations = 7;
  //   int num_variables = 15;

  //   vector<linear_expr> exprs;
  //   for (int i = 0; i < num_equations; i++) {
  //     exprs.push_back(random_linear_expression(num_variables));
  //   }

  //   vector<unique_ptr<formula> > fms;
  //   vector<formula*> fm_ptrs;
  //   for (auto expr : exprs) {
  //     int rc = rand() % 3;
  //     comparator c = EQUAL;
  //     if (rc == 0) {
  // 	c = EQUAL;
  //     } else if (rc == 1) {
  // 	c = LESS;
  //     } else {
  // 	c = GREATER;
  //     }
  //     fms.push_back(mk_atom(c, expr));
  //     fm_ptrs.push_back(fms.back().get());
  //   }
    
  //   // unique_ptr<formula> p_gtz = mk_atom(LESS, p);
  //   // unique_ptr<formula> p_leq = mk_atom(GEQ, q);

  //   unique_ptr<formula> f = mk_conjunction(fm_ptrs); //{p_gtz.get(), p_leq.get()});

  //   vector<order> viable_orders =
  //     all_viable_orders(0, exprs, *f);

  //   cout << "# of viable orders = " << viable_orders.size() << endl;
    
  //   for (auto ord : viable_orders) {
  //     print_order(ord);
  //   }

  //   for (auto& expr : exprs) {
  //     cout << expr << endl;
  //   }

  // }

  
}
