#pragma once
#include "data/storeddatatypes.hpp"
#include <string>
namespace bpmod::convert {
inline std::string SdTypeToStr(const data::SD_TYPES value) {
    std::string str{""};
    if (std::holds_alternative<int>(value)) {
        str += std::to_string(std::get<int>(value));
    } else if (std::holds_alternative<double>(value)) {
        str += std::to_string(std::get<double>(value));
    } else if (std::holds_alternative<std::string>(value)) {
        str += std::get<std::string>(value);
    } else if (std::holds_alternative<bool>(value)) {
        str += std::to_string(std::get<bool>(value));
    }
    return str;
}
}