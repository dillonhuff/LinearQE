#pragma once

#include <gmp.h>
#include <string>

namespace lqe {

  class rational {
  protected:
    mpq_t val;

  public:
    rational(mpq_t tmp) {
      mpq_init(val);
      mpq_swap(val, tmp);
      mpq_canonicalize(val);
    }

    rational(const std::string& value) {
      mpq_init(val);
      mpq_set_str(val, value.c_str(), 10);
      mpq_canonicalize(val);
    }

    int sign() const { return mpq_sgn(val); }

    bool equals(const rational& l) const {
      if (mpq_equal(val, l.val)) {
	return true;
      }
      return false;
    }

    rational plus(const rational& l) const {
      mpq_t sum;
      mpq_init(sum);
      mpq_add(sum, val, l.val);
      return rational(sum);
    }
    
  };

  inline rational operator+(const rational& l, const rational& r) {
    return l.plus(r);
  }

  inline bool operator==(const rational& l, const rational& r) {
    return l.equals(r);
  }

  inline bool operator!=(const rational& l, const rational& r) {
    return !(l == r);
  }
  
}
