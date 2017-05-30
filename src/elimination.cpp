#include "elimination.h"

#include <cassert>

#include "algorithm.h"

using namespace std;

namespace lqe {

  std::vector<int>
  conjunction_sat_intervals_wrt_table(const sign_table& t,
				      const conjunction& atm) {
    vector<int> vals = t.all_intervals();
    for (auto clause : atm) {
      auto intervals = sat_intervals_wrt_table(t, *clause);
      vals = intersection(vals, intervals);
    }
    return vals;
  }

  std::vector<int>
  disjunction_sat_intervals_wrt_table(const sign_table& t,
				      const disjunction& atm) {
    vector<int> vals = {};
    for (auto clause : atm) {
      auto intervals = sat_intervals_wrt_table(t, *clause);
      concat(vals, intervals);
    }
    return vals;
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
      return disjunction_sat_intervals_wrt_table(t,
						 static_cast<const disjunction&>(f));

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

  std::unique_ptr<formula>
  project_formula(const std::vector<int>& vars_to_remove, const formula& fm) {
    return mk_true();
  }

  std::vector<order>
  all_viable_orders(const int variable,
		    const std::vector<linear_expr>& exprs,
		    const formula& f) {
    vector<order> acceptable;
    for (auto& order : all_orders(inds(exprs))) {
      sign_table st(variable, exprs, order);
      if (is_sat_wrt_table(st, &f)) {
	acceptable.push_back(order);
      }
    }

    return acceptable;
  }
  
}
