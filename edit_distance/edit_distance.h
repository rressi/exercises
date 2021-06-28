#pragma once

#include <string_view>

namespace edit_distance {

using StringView = std::string_view;
using MaxDistance = long;

bool matchStrings(StringView a, StringView b, MaxDistance maxDistance = -1);

} // namespace edit_distance