#pragma once
#include <string>
namespace bpmod::data {
struct Values {
    int a;
    float b;
    std::string c;
    Values();
    Values(
        int a,
        double b,
        std::string c
    );
};
} // namespace bpmod::data


