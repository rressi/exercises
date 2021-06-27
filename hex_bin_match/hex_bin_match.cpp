#include "hex_bin_match.h"

#include <algorithm>


namespace hex_bin_match {

bool matchHexAndBin(HexStringView hex,
                    BinStringView bin) {

    constexpr auto BITS_PER_HEX_DIGIT = 4;

    unsigned x = 0U, y = 0U;
    while (x == y
           && !hex.empty()
           && !bin.empty()) {

        std::tie(x, hex) = readHexDigit(hex);
        std::tie(y, bin) = readBinDigits(bin, BITS_PER_HEX_DIGIT);
    }

    return x == y && hex.empty() && bin.empty();
}

auto readBinDigits(BinStringView bin, unsigned n)
-> std::tuple<unsigned, BinStringView> {

    n = std::min(n, unsigned(bin.size()));
    if (n > sizeof(unsigned) * 8) {
        throw std::runtime_error(
                "I cannot fit N digits into an unsigned number");
    }

    unsigned x = 0U;
    for (unsigned i = 0U; i < n; i++) {
        x = x | decodeBinDigit(bin.back()) << i;
        bin.remove_suffix(1);
    }

    return {x, bin};
}

auto readHexDigit(HexStringView hex)
-> std::tuple<unsigned, HexStringView> {

    if (hex.empty()) return {};

    auto x = decodeHexDigit(hex.back());
    hex.remove_suffix(1);

    return {x, hex};
}

unsigned decodeBinDigit(char digit) {

    switch (digit) {
        case '0':
            return 0;
        case '1':
            return 1;
        default:
            throw std::runtime_error("Not a binary digit");
    }

}

auto decodeHexDigit(char digit) -> unsigned {

    switch (digit) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;

        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;

        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;

        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;

        default:
            throw std::runtime_error("Not an hexadecimal digit");
    }

}

} // namespace hex_bin_match
