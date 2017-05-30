#include "order.h"

using namespace std;

namespace lqe {

  std::vector<order> update_orders(const unsigned fresh, const order& ord) {
    vector<order> ords;

    // Add one new order for each equivalence class in the original order, where
    // the new element is in the existing equivalence class
    for (int i = 0; i < ord.size(); i++) {
      order fresh;

      for (int j = 0; j < i; j++) {
	fresh.push_back(ord[j]);
      }

      equivalence_group g = ord[i];
      g.push_back(i);
      fresh.push_back(g);
      
      for (int j = i + 1; j < ord.size(); j++) {
	fresh.push_back(ord[j]);
      }

      ords.push_back(fresh);

    }

    // Create order where the new element is the largest element
    order i_is_max = ord;
    i_is_max.push_back({fresh});
    ords.push_back(i_is_max);

    // Create groups where the new element is in between or smallest
    for (int i = 0; i < ord.size(); i++) {
      order fresh_ord;

      for (int j = 0; j < i; j++) {
	fresh_ord.push_back(ord[j]);
      }
      fresh_ord.push_back({fresh});
      for (int j = i + 1; j < ord.size(); j++) {
	fresh_ord.push_back(ord[j]);
      }

      ords.push_back(fresh_ord);
    }

    return ords;
  }

}
