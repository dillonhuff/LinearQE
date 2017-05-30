#include "formula.h"

using namespace std;

namespace lqe {

  std::unique_ptr<false_fm> mk_false() {
    return unique_ptr<false_fm>(new false_fm());
  }

  std::unique_ptr<true_fm> mk_true() {
    return unique_ptr<true_fm>(new true_fm());
  }
  
  std::unique_ptr<atom> mk_atom(const comparator c, const linear_expr& lx) {
    return unique_ptr<atom>(new atom(c, lx));
  }

  unique_ptr<conjunction> mk_conjunction(const std::vector<formula*>& lx) {
    return unique_ptr<conjunction>(new conjunction(lx));
  }

  unique_ptr<disjunction> mk_disjunction(const std::vector<formula*>& lx) {
    return unique_ptr<disjunction>(new disjunction(lx));
  }

}
