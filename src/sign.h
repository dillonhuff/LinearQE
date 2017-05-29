#pragma once

namespace lqe {

  enum sign { POSITIVE, NEGATIVE, ZERO };

  inline sign flip(const sign s) {
    if (s == POSITIVE) { return NEGATIVE; }
    if (s == NEGATIVE) { return POSITIVE; }
    return s;
  }


}
