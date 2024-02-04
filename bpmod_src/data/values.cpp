#include "values.hpp"
namespace bpmod::data {
Values::Values() :
    a(0),
    b(0.0),
    c("")
{}
Values::Values(
    int a,
    double b,
    std::string c
) :
    a(a),
    b(b),
    c(c)
{}
} // namespace bpmod::data
