#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>

#include "data/values.hpp"
#include "data/storedvalues.hpp"
#include "writer/store.hpp"

#include "maker/maker.hpp"
#include "maker/data/makerdata.hpp"

#include "iterator/genericgenerator.hpp"


BOOST_PYTHON_MODULE(bpmod) {
boost::python::
class_<bpmod::maker::data::MakerData>("MakerData")
    .def_readwrite("number",&bpmod::maker::data::MakerData::number)
    .add_property("values",
        //getter
        // &getMakerDataValuesList,
        +[](const bpmod::maker::data::MakerData &self) {
                boost::python::list list;
            for (const auto &i : self.values) {
                list.append(i);
            }
            return list;
        },
        //setter
        +[](bpmod::maker::data::MakerData &self,
            boost::python::list list) {
            self.values={
                std::vector<int> (
                    boost::python::stl_input_iterator<int>(list),
                    boost::python::stl_input_iterator<int>()
                )
            };
        }
    )
    .def("__repr__",&bpmod::maker::data::MakerData::__repr__)
    .def("__str__",&bpmod::maker::data::MakerData::__str__)
;


boost::python::
class_<bpmod::maker::Maker,
        boost::shared_ptr<bpmod::maker::Maker>,
        boost::noncopyable>
        ("Maker", boost::python::no_init)
    .def(boost::python::init<>())
    .def(boost::python::init<const int &, const int &>())
    .add_property("seed", &bpmod::maker::Maker::getSeed,
                          &bpmod::maker::Maker::setSeed
     )
     .add_property("amountToRun", &bpmod::maker::Maker::getAmountToRun,
                                  &bpmod::maker::Maker::setAmountToRun
     )
     .def("run",&bpmod::maker::Maker::run)
;

boost::python::
class_<bpmod::iterator::GenericGenerator,
       boost::shared_ptr<bpmod::iterator::GenericGenerator>,
       boost::noncopyable >("GenericGenerator",
       boost::python::no_init)
    .def(boost::python::init<>())
    .def(boost::python::init<boost::python::object>())
    .def("__iter__",&bpmod::iterator::GenericGenerator::__iter__,
                    boost::python::return_self<>())
    .def("__next__",&bpmod::iterator::GenericGenerator::__next__)
    .def("setHold",&bpmod::iterator::GenericGenerator::setHold)
;

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
    .add_property("storedValues",&bpmod::writer::Store::storedValues,
        "StoredValues: Type")
    .def("setHeaderLines",&bpmod::writer::Store::setHeaderLines)
    .def("writeLine",&bpmod::writer::Store::writeLine)
    .def("writeArgs",
        boost::python::raw_function(&bpmod::writer::Store::writeArguments))
    .def("setTailLines",&bpmod::writer::Store::setTailLines)
;

} // BOOST_PYTHON_MODULE(bpmod)