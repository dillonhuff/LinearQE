#pragma once

#include "formula.h"
#include "order.h"
#include "sign_table.h"

namespace lqe {

  bool is_sat_wrt_table(const sign_table& t,
			const formula* const f);

  std::vector<int>
  sat_intervals_wrt_table(const sign_table& t,
			  const formula& f);


  std::unique_ptr<formula>
  project_formula(const std::vector<int>& vars_to_remove, const formula&);

  std::vector<order>
  all_viable_orders(const int variable,
		    const std::vector<linear_expr>& exprs,
		    const formula& f);
}
