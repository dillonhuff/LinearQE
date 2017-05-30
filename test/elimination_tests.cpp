#include <memory>

#include "catch.hpp"

#include "linear_expr.h"
#include "formula.h"
#include "sign_table.h"

using namespace std;

namespace lqe {

  TEST_CASE("x > 0 is satisfied") {
    linear_expr x(1, {{"1"}});

    sign_table st(0, {x}, {{0}});

    unique_ptr<formula> f = unique_ptr<formula>(new atom(GREATER, x));

    
  }
}
