#include "genericgenerator.hpp"
namespace bpmod::iterator {
GenericGenerator::GenericGenerator() : 
    hold(boost::python::object()),
    current(boost::python::object())
{}
GenericGenerator::GenericGenerator(boost::python::object ref) :
    hold(ref),
    current(boost::python::object()){
    if (!PyObject_HasAttrString(hold.ptr(), "run")) {
            PyErr_SetString(PyExc_AttributeError,
            "Provided object does not have 'run' attribute");
            boost::python::throw_error_already_set();
    }
}
GenericGenerator::GenericGenerator(const GenericGenerator &o) {
    *this=o;
}
GenericGenerator &GenericGenerator::operator=(const GenericGenerator &o) {
    this->hold=o.hold;
    this->current=o.current;
    return *this;
}
GenericGenerator::~GenericGenerator() {
    this->hold=boost::python::object();
    this->current=boost::python::object();
}
boost::python::object GenericGenerator::__iter__() {
    return boost::python::object(boost::python::ptr(this));
}
boost::python::object GenericGenerator::__next__() {
    try {
        this->current = hold.attr("run")();
        if (this->current == boost::python::object()) {
            PyErr_SetNone(PyExc_StopIteration);
                boost::python::throw_error_already_set();
            }
    } catch (boost::python::error_already_set const&) {
        boost::python::throw_error_already_set();
    }
    return this->current;
}
void GenericGenerator::setHold(boost::python::object ref) {
    if (!PyObject_HasAttrString(ref.ptr(), "run")) {
            PyErr_SetString(PyExc_AttributeError,
            "Provided object does not have 'run' attribute");
            boost::python::throw_error_already_set();
    }
    this->hold=ref;
}
}