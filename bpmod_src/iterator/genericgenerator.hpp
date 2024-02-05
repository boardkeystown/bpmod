#pragma once
#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>
namespace bpmod::iterator {
class GenericGenerator {
private:
    boost::python::object hold;
    boost::python::object current;
public:
    GenericGenerator();
    GenericGenerator(boost::python::object ref);
    GenericGenerator(const GenericGenerator &o);
    GenericGenerator &operator=(const GenericGenerator &o);
    ~GenericGenerator();
    boost::python::object __iter__();
    boost::python::object __next__();
    void setHold(boost::python::object ref);
};
}