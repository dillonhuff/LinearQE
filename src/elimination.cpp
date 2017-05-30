#include "elimination.h"

#include <cassert>

namespace lqe {

  std::vector<int>
  sat_intervals_wrt_table(const sign_table& t,
			 const formula& f) {
    switch (f.formula_type()) {
    case FM_ATOM:
      return {};
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
