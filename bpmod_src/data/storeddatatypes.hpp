#pragma once
#include <variant>
#include <string>
namespace bpmod::data {
using SD_TYPES = std::variant<std::monostate, int, double, std::string, bool>;
} // namespace bpmod::data