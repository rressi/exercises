#include "robot_navigator.h"

namespace dynamic_programming::robot_navigator {


bool Pos::operator==(const Pos &other) const {
    return x == other.x && y == other.y;
}

[[nodiscard]] auto Pos::left() const -> Pos {
    return Pos{x - 1, y};
}

[[nodiscard]] auto Pos::up() const -> Pos {
    return Pos{x, y - 1};
}

class RobotNavigator {

public:
    explicit RobotNavigator(Blockers blockers)
            : blockers_(std::move(blockers)) {
        height = int(blockers_.size());
        if (height > 0) {
            width = int(blockers_.front().size());
        }
    }

    [[nodiscard]] auto getWidth() const -> int {
        return width;
    }

    [[nodiscard]] auto getHeight() const -> int {
        return height;
    }

    [[nodiscard]] auto findRoute(Pos from, Pos to) -> Opt<Path>;

private:

    [[nodiscard]] bool isValid(const Pos &pos) const;

    void invalidate(const Pos &pos);

    Blockers blockers_{};
    int width{};
    int height{};
};

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
    if (pos.y >= 0 && pos.y < int(this->blockers_.size())) {
        const auto &row = this->blockers_.at(pos.y);
        if (pos.x >= 0 && pos.x < int(row.size())) {
            return !row.at(pos.x);
        }
    }
    return false;
}

void RobotNavigator::invalidate(const Pos &pos) {
    if (pos.y >= 0 && pos.y < int(this->blockers_.size())) {
        auto &row = this->blockers_.at(pos.y);
        if (pos.x >= 0 && pos.x < int(row.size())) {
            row.at(pos.x) = true;
        }
    }
}

auto findRoute(Blockers blockers) -> Opt<Path> {
    auto navigator = RobotNavigator(std::move(blockers));
    return navigator.findRoute({}, {navigator.getWidth() - 1, navigator.getHeight() - 1});
}

} // namespace dynamic_programming