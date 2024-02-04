#pragma once
#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>
#include "data/storeddatatypes.hpp"
namespace bpmod::convert {
inline data::SD_TYPES PyToCppType(
    const boost::python::object &object
) {
    std::string errorMsg {"Object is of unknown and unsupported type: "};
    data::SD_TYPES cppType = std::monostate{};
    if (!object.is_none() && 
         boost::python::extract<int>(object).check()) {
        cppType = boost::python::extract<int>(object);
    } else if (!object.is_none() && 
                boost::python::extract<double>(object).check()) {
        cppType = boost::python::extract<double>(object);
    }  else if (!object.is_none() && 
                 boost::python::extract<std::string>(object).check()) {
        cppType = boost::python::extract<std::string>(object);
    } else if (!object.is_none() && 
                boost::python::extract<bool>(object).check()) {
        cppType = boost::python::extract<bool>(object);
    } else if (object.is_none()) {
        // is none type
        errorMsg += "None";
        PyErr_SetString(
            PyExc_AttributeError, errorMsg.c_str()
        );
        boost::python::throw_error_already_set();
    } else {
        // unknown and unsupported type
        boost::python::str typeName = boost::python::
            extract<boost::python::str>(
                object.attr("__class__").attr("__name__")
            );
        errorMsg += boost::python::extract<std::string>(typeName);
        PyErr_SetString(
            PyExc_AttributeError, errorMsg.c_str()
        );
        boost::python::throw_error_already_set();
    }
    return cppType;
}
} // namespace bpmod::convert