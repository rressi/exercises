#pragma once

#include <limits>
#include <string_view>

namespace edit_distance {

using StringView = std::string_view;
using Distance = unsigned;

bool matchStrings(StringView s, StringView t, Distance maxDistance);

auto calculateEditDistance(StringView s, StringView t) -> Distance;

} // namespace edit_distance