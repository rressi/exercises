#include "recursive_multiply.h"

#include <cstdint>

namespace numbers {

auto recursiveMultiply(std::uint32_t a, std::uint32_t b) -> std::uint64_t {
  if (a == 0) return 0;

  auto y = std::uint64_t(a & 1 ? b : 0);
  return y + (recursiveMultiply(a >> 1U, b) << 1U);
}

}  // namespace numbers
