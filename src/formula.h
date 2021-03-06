#pragma once

#include <iostream>
#include <memory>

#include "linear_expr.h"

namespace lqe {

  enum comparator { GREATER, LESS, EQUAL, LEQ, GEQ };

  enum fm_type { FM_ATOM, FM_CONJUNCTION, FM_DISJUNCTION, FM_NEGATION, FM_TRUE, FM_FALSE };

  class formula {
  public:
    virtual fm_type formula_type() const = 0;
    virtual void print(std::ostream& out) const = 0;
  };

  class atom : public formula {
  protected:
    comparator c;
    linear_expr lx;

  public:
    atom(const comparator p_c, const linear_expr& p_lx) : c(p_c), lx(p_lx) {}

    comparator predicate() const { return c; }

    const linear_expr& expr() const { return lx; }

    void print(std::ostream& out) const {
      out << "( " << lx << " " << " 0 )" << std::endl;
    }

    fm_type formula_type() const { return FM_ATOM; }
  };

  class conjunction : public formula {
  protected:
    std::vector<formula*> fms;
    
  public:
    conjunction(const std::vector<formula*>& p_fms) : fms(p_fms) {
    }

    void print(std::ostream& out) const {
    }

    std::vector<formula*>::const_iterator begin() const { return std::begin(fms); }
    std::vector<formula*>::const_iterator end() const { return std::end(fms); }

    fm_type formula_type() const { return FM_CONJUNCTION; }
  };

  class disjunction : public formula {
  protected:
    std::vector<formula*> fms;
    
  public:
    disjunction(const std::vector<formula*>& p_fms) : fms(p_fms) {
    }

    void print(std::ostream& out) const {}

    std::vector<formula*>::const_iterator begin() const { return std::begin(fms); }
    std::vector<formula*>::const_iterator end() const { return std::end(fms); }

    fm_type formula_type() const { return FM_DISJUNCTION; }
  };

  class true_fm : public formula {
  public:
    fm_type formula_type() const { return FM_TRUE; }
    void print(std::ostream& out) const {}
  };
  
  class false_fm : public formula {
  public:
    fm_type formula_type() const { return FM_FALSE; }
    void print(std::ostream& out) const {}
  };

  std::unique_ptr<atom> mk_atom(const comparator c, const linear_expr& lx);
  std::unique_ptr<conjunction> mk_conjunction(const std::vector<formula*>& lx);
  std::unique_ptr<disjunction> mk_disjunction(const std::vector<formula*>& lx);
  std::unique_ptr<false_fm> mk_false();
  std::unique_ptr<true_fm> mk_true();

  inline bool operator==(const formula& l, const formula& r) {
    return true;
  }

  std::ostream& operator<<(std::ostream& out, const formula& r);
  
}
