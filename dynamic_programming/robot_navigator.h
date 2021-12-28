#pragma once

#include <optional>
#include <vector>

namespace dynamic_programming::robot_navigator {

struct Pos {
    int x{};
    int y{};
};

inline bool operator==(const Pos &a, const Pos &b) {
    return a.x == b.x && a.y == b.y;
}

using Blockers = std::vector<std::vector<bool>>;

using Path = std::vector<Pos>;

template <class T>
using Opt = std::optional<T>;

auto findPath(Blockers blockers) -> Opt<Path>;

}  // namespace dynamic_programming::robot_navigator