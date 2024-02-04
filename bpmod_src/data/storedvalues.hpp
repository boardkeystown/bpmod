#pragma once
#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>
#include <map>
#include <string>
#include "storeddatatypes.hpp"
namespace bpmod::data {
class StoredValues {
private:
    boost::python::dict dict;
public:
    StoredValues();
    ~StoredValues();
    std::map<std::string, SD_TYPES > getValues() const;
    // exposed to python
    void setAttr(
        const std::string &name,
        const boost::python::object &value
    );
    static boost::python::object getAttr(
        const StoredValues &self,
        const std::string &name
    );
    boost::python::dict getValuesDict() const;
    boost::python::object get(
        const std::string &key,
        const boost::python::object &defaultValue = boost::python::object()
    ) const;
    void delItem(const std::string &key);
};
} // namespace bpmod::data