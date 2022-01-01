#include "color.h"

#include <stdexcept>


namespace graph {

auto toString(Color color) -> std::string {
    switch (color) {
        case Color::Black:
            return "Black";
        case Color::Blue:
            return "Blue";
        case Color::Green:
            return "Green";
        case Color::Orange:
            return "Orange";
        case Color::Red:
            return "Red";
        case Color::Yellow:
            return "Yellow";
        case Color::White:
            return "White";
    }

    throw std::runtime_error("Invalid color");
}

auto toString(const ColorList& colorList) -> std::string {
    auto buffer = std::string();
    auto separator = "";
    for (auto color : colorList) {
        buffer.append(separator);
        buffer.append(toString(color));
        separator = "_";
    }
    return buffer;
}

}  // namespace graph
