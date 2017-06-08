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
      // cout << "Sat intervals on clause = ";
      // for (auto i : intervals) {
      // 	cout << i << " ";
      // }
      // cout << endl;

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
    if (expr_index < 0) {
      //cout << "Table does not contain " << atm.expr() << endl;
      return t.all_intervals();
    }

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
  all_viable_eager(const int variable,
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
  
  std::vector<order>
  all_viable_orders(const int variable,
		    const std::vector<linear_expr>& exprs,
		    const formula& f) {

    vector<order> last_orders = {{{0}}};
    for (int i = 1; i < exprs.size(); i++) {
      //cout << "i = " << i << " # of orders = " << last_orders.size() << endl;
      vector<linear_expr> expr_subset_im1;
      for (int j = 0; j < i; j++) {
      	expr_subset_im1.push_back(exprs[j]);
      }

      vector<order> next_orders;
      for (auto& current_ord : last_orders) {
	//cout << "next orders size = " << next_orders.size() << endl;
	sign_table st(variable, expr_subset_im1, current_ord);

	if (is_sat_wrt_table(st, &f)) {
	  concat(next_orders, update_orders(i, current_ord));
	}
      }

      last_orders = next_orders;

    }

    //cout << "# of orders before postprocessing = " << last_orders.size() << endl;

    vector<order> acceptable;
    for (auto& current_ord : last_orders) {
      sign_table st(variable, exprs, current_ord);

      if (is_sat_wrt_table(st, &f)) {
	acceptable.push_back(current_ord);
	//concat(next_orders, update_orders(i, current_ord));
      }
    }

    return acceptable;
  }

  std::vector<linear_expr> collect_expressions(const formula& f) {
    return {};
  }

  formula* substitute_variable(const formula& f,
			       const int i,
			       const linear_expr& root) {
    return nullptr;
  }

  std::unique_ptr<formula> ferrante_rackoff(const int i, const formula& f) {
    vector<linear_expr> exprs = collect_expressions(f);

    vector<formula*> fms;
    // Add zero points intervals
    for (auto& expr : exprs) {
      linear_expr root = expr.symbolic_root(i);
      fms.push_back(substitute_variable(f, i, root));
    }

    // Add midpoint interval tests
    for (int j = 0; j < exprs.size(); j++) {
      for (int k = 0; k < exprs.size(); k++) {
	if (j != k) {
	  const linear_expr& ej = exprs[j];
	  const linear_expr& ek = exprs[k];
	  linear_expr midpoint = (ej + ek).scalar_times({"1/2"});
	  fms.push_back(substitute_variable(f, i, midpoint));
	}
      }
    }

    // Add negative infinity points
    for (auto& expr : exprs) {
      linear_expr root = expr.symbolic_root(i);
      linear_expr test_pt = root.add_constant({"-1"});
      fms.push_back(substitute_variable(f, i, test_pt));
    }

    // Add positive infinity points
    for (auto& expr : exprs) {
      linear_expr root = expr.symbolic_root(i);
      linear_expr test_pt = root.add_constant({"1"});
      fms.push_back(substitute_variable(f, i, test_pt));
    }
    
    return mk_disjunction(fms);
  }
  
}
