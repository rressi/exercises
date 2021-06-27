#pragma once

#include <string>
#include <tuple>

namespace hex_bin_match {

using BinStringView = std::string_view;
using HexStringView = std::string_view;

bool matchHexAndBin(HexStringView hex, BinStringView bin);

auto readBinDigits(BinStringView bin, unsigned n) -> std::tuple<unsigned, BinStringView>;

auto readHexDigit(HexStringView hex) -> std::tuple<unsigned, HexStringView>;

auto decodeBinDigit(char digit) -> unsigned;

auto decodeHexDigit(char digit) -> unsigned;

} // namespace hex_bin_match

