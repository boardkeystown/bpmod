#pragma once
#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>
#include "filewriter.hpp"
#include "data/storedvalues.hpp"
namespace bpmod::writer {
class Store {
public:
    FileWriter fileWriter;
    data::StoredValues storedValues;
public:
    Store();
    ~Store();
    void setHeaderLines(
        boost::python::list headLines
    );
    void writeLine(
        boost::python::str fileName,
        boost::python::str line
    );
    static boost::python::object writeArguments(
        const boost::python::tuple &args,
        const boost::python::dict &kwargs
    );
    void setTailLines(
        boost::python::list headLines
    );
};
} // namespace bpmod::writer
