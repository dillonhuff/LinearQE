#pragma once

#include "formula.h"
#include "sign_table.h"

namespace lqe {

  bool is_sat_wrt_table(const sign_table& t,
			const formula* const f);

  std::vector<int>
  sat_intervals_wrt_table(const sign_table& t,
			  const formula& f);


}
