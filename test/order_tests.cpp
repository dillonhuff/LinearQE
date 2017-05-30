#include "catch.hpp"

#include "algorithm.h"
#include "linear_expr.h"
#include "order.h"

using namespace std;

namespace lqe {

  int total_elements(const order& ord) {
    int elems = 0;

    for (int i = 0; i < ord.size(); i++) {
      elems += ord[i].size();
    }

    return elems;
  }

  void print_order(const order& ord) {
    for (int i = 0; i < ord.size(); i++) {
      cout << "[ ";
      for (int j = 0; j < ord[i].size(); j++) {
	cout << ord[i][j] << " ";
      }
      cout << "] ";
    }
    cout << endl;
  }

  TEST_CASE("3 orders of 2 roots") {
    vector<order> orders = update_orders(1, {{0}});

    SECTION("All orders include 0, 1") {
      for (auto ord : orders) {
	auto elems = concat_all(ord);

	REQUIRE(elem(0, elems));
	REQUIRE(elem(1, elems));
      }
    }
    
    for (auto& ord : orders) {
      print_order(ord);
    }

    cout << "DONE WITH 2 test" << endl;

    REQUIRE(orders.size() == 3);
  }

  TEST_CASE("24 orders of 3 roots") {
    vector<order> orders = all_orders({0, 1, 2});

    for (auto ord : orders) {
      print_order(ord);
    }

    SECTION("All orders have 3 elements total") {
      for (auto ord : orders) {
	REQUIRE(total_elements(ord) == 3);
      }
    }

    SECTION("All orders include 0, 1, and 2") {
      for (auto ord : orders) {
	auto elems = concat_all(ord);

	REQUIRE(elem(0, elems));
	REQUIRE(elem(1, elems));
	REQUIRE(elem(2, elems));
      }
    }
    
    REQUIRE(orders.size() == 13);
  }

}
