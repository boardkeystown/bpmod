#pragma once
#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>
#include <string>
#include <vector>
namespace bpmod::writer::utils {
std::vector<std::string> pyListStrToVector(
    const boost::python::list &list
);
} //bpmod::writer::utils