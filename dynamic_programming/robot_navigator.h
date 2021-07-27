#pragma once

#include <vector>
#include <optional>

namespace dynamic_programming::robot_navigator {

template<class T>
using Opt = std::optional<T>;

struct Pos {
    int x{};
    int y{};

    bool operator==(const Pos &other) const;

    [[nodiscard]] auto left() const -> Pos;

    [[nodiscard]] auto up() const -> Pos;
};

using Path = std::vector<Pos>;

using Blockers = std::vector<std::vector<bool>>;

auto findRoute(Blockers blockers) -> Opt<Path>;


} // namespace dynamic_programming::robot_navigator