#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>

#include "data/values.hpp"
#include "data/storedvalues.hpp"
#include "writer/store.hpp"

BOOST_PYTHON_MODULE(bpmod) {
boost::python::
class_<bpmod::data::Values>("Values")
    .def(boost::python::init<int,double,std::string>())
    .def_readwrite("a",&bpmod::data::Values::a)
    .def_readwrite("b",&bpmod::data::Values::b)
    .def_readwrite("c",&bpmod::data::Values::c)
;

boost::python::
class_<bpmod::data::StoredValues>("StoredValues")
    .def("__setattr__", &bpmod::data::StoredValues::setAttr)
    .def("__getattr__", &bpmod::data::StoredValues::getAttr)
    .def("__setitem__", &bpmod::data::StoredValues::setAttr)
    .def("__getitem__", &bpmod::data::StoredValues::getAttr)
    .def("get",         &bpmod::data::StoredValues::get)
    .def("getValues",   &bpmod::data::StoredValues::getValuesDict)
    .def("delItem",   &bpmod::data::StoredValues::delItem)
;

boost::python::
class_<bpmod::writer::Store>("Store")
    .add_property("storedValues",&bpmod::writer::Store::storedValues,"StoredValues: Type")
    .def("setHeaderLines",&bpmod::writer::Store::setHeaderLines)
    .def("writeLine",&bpmod::writer::Store::writeLine)
    .def("writeArgs",boost::python::raw_function(&bpmod::writer::Store::writeArguments))
    .def("setTailLines",&bpmod::writer::Store::setTailLines)
;



}