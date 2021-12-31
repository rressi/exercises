#pragma once

#include <functional>
#include <iterator>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "node.pb.h"

namespace linked_list {

inline bool operator<(const Node& a, const Node& b) {
    return a.value() < b.value();
}

}  // namespace linked_list
