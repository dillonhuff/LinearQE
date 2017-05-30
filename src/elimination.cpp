#include "elimination.h"

#include <cassert>

using namespace std;

namespace lqe {

  std::vector<int>
  atom_sat_intervals_wrt_table(const sign_table& t,
			       const atom& atm) {
    vector<int> intervals;
    sign allowed = POSITIVE;
    if (atm.predicate() == GREATER) {
      allowed = POSITIVE;
    } else if (atm.predicate() == LESS) {
      allowed = NEGATIVE;
    } else {
      allowed = ZERO;
    }

    int expr_index = t.column_of(atm.expr());
    for (int i = 0; i < t.num_rows(); i++) {
      if (t.sign_on_interval(expr_index, i) == allowed) {
	intervals.push_back(i);
      }
    }

    return intervals;
  }

  std::vector<int>
  sat_intervals_wrt_table(const sign_table& t,
			  const formula& f) {
    switch (f.formula_type()) {
    case FM_ATOM:
      return atom_sat_intervals_wrt_table(t, static_cast<const atom&>(f));
    case FM_CONJUNCTION:
      return {};
    case FM_DISJUNCTION:
      return {};
    case FM_NEGATION:
      return {};
    default:
      assert(false);
    }
  }

  bool is_sat_wrt_table(const sign_table& t,
			const formula* const f) {
    return sat_intervals_wrt_table(t, *f).size() > 0;
  }

}
