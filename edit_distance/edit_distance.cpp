
#include "edit_distance.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <tuple>
#include <vector>

namespace edit_distance {

using Matrix = std::vector<std::vector<int>>;
using MatchCase = std::tuple<int, int, int>;
using MatchQueue = std::vector<MatchCase>;

namespace {

auto createMatchMatrix(const StringView &a, const StringView &b) -> Matrix {
    Matrix matrix{};
    matrix.resize(a.size() + 1);
    for (auto &row: matrix) {
        row.resize(b.size() + 1, std::numeric_limits<int>::max());
    }
    return matrix;
}

void pushMatchCase(MatchQueue *queue, Matrix *matrix, int i, int j, int distance) {
    assert(queue);
    assert(matrix);

    distance = std::min(distance, (*matrix)[i][j]);
    (*matrix)[i][j] = distance;

    queue->emplace_back(i, j, distance);
}

} // namespace

bool matchStrings(StringView a, StringView b, MaxDistance maxDistance) {

    if (a.empty() && b.empty()) {
        return true;
    }
    if (a.size() > b.size()) {
        std::swap(a, b);
    }
    if (b.size() - a.size() > maxDistance) {
        return false;
    }

    auto matrix = createMatchMatrix(a, b);

    auto queue = MatchQueue();
    pushMatchCase(&queue, &matrix, 0, 0, 0);

    while (!queue.empty()) {
        auto[i, j, distance] = queue.back();
        queue.pop_back();

        if (i + maxDistance - distance == a.size()
            && j + maxDistance - distance == b.size()) {
            return true;
        }

        distance += int(a[i] != b[j]);
        if (distance <= maxDistance) {
            if (i < a.size()) pushMatchCase(&queue, &matrix, i + 1, j, distance);
            if (j < b.size()) pushMatchCase(&queue, &matrix, i, j + 1, distance);
            if (i < a.size() && j < b.size()) pushMatchCase(&queue, &matrix, i + 1, j + 1, distance);
        }
    }

    return false;
}

} // namespace edit_distance