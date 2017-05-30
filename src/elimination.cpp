#include "elimination.h"

#include <cassert>

using namespace std;

namespace lqe {

  std::vector<int>
  conjunction_sat_intervals_wrt_table(const sign_table& t,
				      const conjunction& atm) {
    return {};
  }
  
  std::vector<int>
  atom_sat_intervals_wrt_table(const sign_table& t,
			       const atom& atm) {
    vector<int> intervals;
    sign allowed_1 = POSITIVE;
    sign allowed_2 = POSITIVE;
    if (atm.predicate() == GREATER) {
      allowed_1 = POSITIVE;
      allowed_2 = POSITIVE;
    } else if (atm.predicate() == LESS) {
      allowed_1 = NEGATIVE;
      allowed_2 = NEGATIVE;
    } else if (atm.predicate() == GEQ) {
      allowed_1 = ZERO;
      allowed_2 = POSITIVE;
    } else if (atm.predicate() == LEQ) {
      allowed_1 = ZERO;
      allowed_2 = NEGATIVE;
    } else {
      allowed_1 = ZERO;
      allowed_2 = ZERO;
    }

    int expr_index = t.column_of(atm.expr());
    for (int i = 0; i < t.num_rows(); i++) {
      if ((t.sign_on_interval(expr_index, i) == allowed_1) ||
	  (t.sign_on_interval(expr_index, i) == allowed_2)) {
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
      return conjunction_sat_intervals_wrt_table(t,
						 static_cast<const conjunction&>(f));
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
