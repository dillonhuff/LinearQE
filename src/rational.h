#pragma once

#include <gmp.h>
#include <string>

namespace lqe {

  class rational {
  protected:
    mpq_t val;

  public:
    rational(const std::string& value) {
      mpq_init(val);
      mpq_set_str(val, value.c_str(), 10);
      mpq_canonicalize(val);
    }

    int sign() const { return mpq_sgn(val); }
    
  };

}
