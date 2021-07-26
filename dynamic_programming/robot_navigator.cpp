#include "robot_navigator.h"

namespace dynamic_programming {

RobotNavigator::RobotNavigator(Grid grid)
        : grid(std::move(grid)) {
}

bool RobotNavigator::Pos::operator==(const Pos &other) const {
    return x == other.x && y == other.y;
}

[[nodiscard]] auto RobotNavigator::Pos::left() const -> Pos {
    return Pos{x - 1, y};
}

[[nodiscard]] auto RobotNavigator::Pos::up() const -> Pos {
    return Pos{x, y - 1};
}

auto RobotNavigator::findRoute(Pos from, Pos to) -> Opt<Path> {

    if (this->isValid(to)) {
        if (from == to) {
            return Path{from};
        }

        if (to.x > from.x) {
            if (this->isValid(to.left())) {
                if (auto path = this->findRoute(from, to.left())) {
                    path->push_back(to);
                    return path;
                }
            }
        }
        if (to.y > from.y) {
            if (this->isValid(to.up())) {
                if (auto path = this->findRoute(from, to.up())) {
                    path->push_back(to);
                    return path;
                }
            }
        }
    }

    this->invalidate(to);
    return {};
}

bool RobotNavigator::isValid(const Pos &pos) const {
    if (pos.y >= 0 || pos.y < int(this->grid.size())) {
        const auto &row = this->grid.at(pos.y);
        if (pos.x >= 0 || pos.x < int(row.size())) {
            return row.at(pos.x) == Cell::Valid;
        }
    }
    return false;
}

void RobotNavigator::invalidate(const Pos &pos) {
    if (pos.y >= 0 || pos.y < int(this->grid.size())) {
        auto &row = this->grid.at(pos.y);
        if (pos.x >= 0 || pos.x < int(row.size())) {
            row.at(pos.x) = Cell::Invalid;
        }
    }
}


} // namespace dynamic_programming