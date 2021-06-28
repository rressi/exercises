
#include "edit_distance.h"

#include <algorithm>
#include <vector>

namespace edit_distance {


bool matchStrings(StringView s, StringView t, Distance maxDistance) {

    return calculateEditDistance(s, t) <= maxDistance;
}

auto calculateEditDistance(StringView s, StringView t) -> Distance {
    auto matrix = std::vector<std::vector<int>>();
    matrix.resize(s.size() + 1);

    for (auto i = 0; i < matrix.size(); i++) {
        matrix[i].resize(t.size() + 1);
        matrix[i][0] = i;
    }

    auto &firstRow = matrix[0];
    for (auto j = 1; j < firstRow.size(); j++) {
        firstRow[j] = j;
    }

    for (auto i = 0; i < s.size(); i++) {
        for (auto j = 0; j < t.size(); j++) {
            matrix[i + 1][j + 1] = std::min(std::min(matrix[i][j + 1] + 1,
                                                     matrix[i + 1][j] + 1),
                                            matrix[i][j] + int(s[i] != t[j]));
        }
    }

    return matrix.back().back();
}

} // namespace edit_distance