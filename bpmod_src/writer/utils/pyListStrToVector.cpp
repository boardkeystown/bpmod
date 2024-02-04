#include "pyListStrToVector.hpp"
namespace bpmod::writer::utils {
std::vector<std::string> pyListStrToVector(
    const boost::python::list &list
) {
    std::vector<std::string> vec{};
    for (boost::python::ssize_t i=0;
         i < boost::python::len(list); ++i) {
        vec.push_back(boost::python::extract<std::string>(list[i]));
    }
    return vec;
}
} //bpmod::writer::utils