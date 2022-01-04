#include "magic_key.h"

namespace binary_search {

bool hasMagicKey(const std::vector<int>& values) {
  auto firstPos = 0;
  auto numValues = values.size();

  while (numValues > 0) {
    auto pivot = numValues / 2;
    auto x = firstPos + pivot;
    auto y = values.at(x);

    if (x < y) {
      numValues = pivot;
    } else if (x > y) {
      firstPos += pivot;
      numValues -= pivot;
    } else {
      return true;
    }
  }

  return false;
}

}  // namespace binary_search