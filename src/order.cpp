#include "order.h"

#include "algorithm.h"

using namespace std;

namespace lqe {

  std::vector<order> update_orders(const unsigned fresh, const order& ord) {
    vector<order> ords;

    // Add one new order for each equivalence class in the original order, where
    // the new element is in the existing equivalence class
    for (int i = 0; i < ord.size(); i++) {
      order fresh_ord;

      for (int j = 0; j < i; j++) {
	fresh_ord.push_back(ord[j]);
      }

      equivalence_group g = ord[i];
      g.push_back(fresh);
      fresh_ord.push_back(g);
      
      for (int j = i + 1; j < ord.size(); j++) {
	fresh_ord.push_back(ord[j]);
      }

      ords.push_back(fresh_ord);

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
      fresh_ord.push_back({ord[i]});

      for (int j = i + 1; j < ord.size(); j++) {
	fresh_ord.push_back(ord[j]);
      }

      ords.push_back(fresh_ord);
    }

    assert(ords.size() == (ord.size()*2 + 1));

    return ords;
  }

  std::vector<order> all_orders(const std::vector<unsigned>& values) {
    if (values.size() == 0) { return {}; }

    // There is one order on one object
    vector<order> ords{{{values[0]}}};

    for (int i = 1; i < values.size(); i++) {
      vector<order> fresh_ords;
      for (auto& ord : ords) {
	concat(fresh_ords, update_orders(values[i], ord));
      }

      ords = fresh_ords;
    }

    return ords;
  }

  int total_elements(const order& ord) {
    int elems = 0;

    for (int i = 0; i < ord.size(); i++) {
      elems += ord[i].size();
    }

    return elems;
  }

  void print_order(const order& ord) {
    for (int i = 0; i < ord.size(); i++) {
      cout << "[ ";
      for (int j = 0; j < ord[i].size(); j++) {
	cout << ord[i][j] << " ";
      }
      cout << "] ";
    }
    cout << endl;
  }

}
