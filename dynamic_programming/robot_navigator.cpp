#include "robot_navigator.h"

namespace dp::robot_navigator {
namespace {

class Grid {
 public:
  explicit Grid(Blockers blockers) : blockers_(std::move(blockers)) {
    height_ = int(blockers_.size());
    if (height_ > 0) {
      width_ = int(blockers_.front().size());
    }
  }

  [[nodiscard]] auto width() const -> int { return width_; }

  [[nodiscard]] auto height() const -> int { return height_; }

  [[nodiscard]] bool isBlocked(const Pos &pos) const {
    if (pos.y >= 0 && pos.y < height_) {
      if (pos.x >= 0 && pos.x < width_) {
        return blockers_[pos.y][pos.x];
      }
    }
    return true;
  }

  void setBlocked(const Pos &pos) {
    if (pos.y >= 0 && pos.y < height_) {
      if (pos.x >= 0 && pos.x < width_) {
        blockers_[pos.y][pos.x] = true;
      }
    }
  }

 private:
  Blockers blockers_{};
  int width_{};
  int height_{};
};

auto findPathRecursion(Grid *grid, const Pos &goal) -> Opt<Path> {
  if (grid->isBlocked(goal)) return {};

  if (goal == Pos{}) {
    return Path{goal};
  }

  if (auto path = findPathRecursion(grid, Pos{goal.x - 1, goal.y})) {
    path->push_back(goal);
    return path;
  }

  if (auto path = findPathRecursion(grid, Pos{goal.x, goal.y - 1})) {
    path->push_back(goal);
    return path;
  }

  grid->setBlocked(goal);
  return {};
}

}  // namespace

auto findPath(Blockers blockers) -> Opt<Path> {
  auto grid = Grid(std::move(blockers));
  auto goalX = std::max(0, grid.width() - 1);
  auto goalY = std::max(0, grid.height() - 1);
  auto goal = Pos{goalX, goalY};
  return findPathRecursion(&grid, goal);
}

}  // namespace dp::robot_navigator
