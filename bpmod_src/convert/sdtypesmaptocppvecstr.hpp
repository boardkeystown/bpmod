#pragma once
#include "data/storeddatatypes.hpp"
#include <map>
#include <vector>
#include <string>
namespace bpmod::convert {
inline std::vector<std::string> SDtypesMapToCppVecStr(
    const std::map<std::string,data::SD_TYPES> &mapSD
) {
    std::vector<std::string> vec_strs;
    std::string temp;
    for (auto &[name,value] : mapSD) {
        temp = "";
        temp += name;
        temp += " : ";
        if (std::holds_alternative<int>(value)) {
            temp += std::to_string(std::get<int>(value));
        } else if (std::holds_alternative<double>(value)) {
            temp += std::to_string(std::get<double>(value));
        } else if (std::holds_alternative<std::string>(value)) {
            temp += std::get<std::string>(value);
        } else if (std::holds_alternative<bool>(value)) {
            temp += std::to_string(std::get<bool>(value));
        } else {
            temp += "?";
        }
        vec_strs.push_back(temp);
    }
    return vec_strs;
}
}