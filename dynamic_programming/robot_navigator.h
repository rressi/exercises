#pragma once

#include <vector>
#include <optional>

namespace dynamic_programming {

template<class T>
using Opt = std::optional<T>;

class RobotNavigator {

public:
    enum class Cell {
        Valid,
        Invalid
    };
    using Grid = std::vector<std::vector<Cell>>;

    explicit RobotNavigator(Grid grid);

    struct Pos {
        int x{};
        int y{};

        bool operator==(const Pos& other) const;
        [[nodiscard]] auto left() const -> Pos;
        [[nodiscard]] auto up() const -> Pos;
    };
    using Path = std::vector<Pos>;

    [[nodiscard]] auto findRoute(Pos from, Pos to) -> Opt<Path>;

private:

    [[nodiscard]] bool isValid(const Pos &pos) const;

    void invalidate(const Pos &pos);

    Grid grid{};

};

} // namespace dynamic_programming