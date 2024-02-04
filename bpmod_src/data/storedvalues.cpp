#include "storedvalues.hpp"
#include "data/storeddatatypes.hpp"
#include "convert/pytocpptype.hpp"
namespace bpmod::data {
StoredValues::StoredValues() {}
StoredValues::~StoredValues() {
    // boost::python::list keys = this->dict.keys();
    // for (boost::python::ssize_t i = 0; 
    //      i < boost::python::len(keys); ++i) {
    //     boost::python::object key = key[i];
    //     // boost::python::object value = this->dict[key];
    //     this->dict[key] = boost::python::object();
    // }
    // this->dict = boost::python::dict();
}
std::map<std::string, SD_TYPES > StoredValues::getValues() const {
    constexpr const boost::python::ssize_t FIRST{0};
    constexpr const boost::python::ssize_t SECOND{1};
    std::map<std::string, SD_TYPES > cppMap;
    boost::python::tuple pair;
    boost::python::object key;
    boost::python::object value;
    std::string strKey;
    SD_TYPES cppValue;
    boost::python::list items = this->dict.items();
    for (boost::python::ssize_t i = 0; i < boost::python::len(items); ++i) {
        pair = boost::python::extract<boost::python::tuple>(items[i]);
        key = pair[FIRST];
        value = pair[SECOND];
        strKey = boost::python::extract<std::string>(key);
        cppValue = convert::PyToCppType(value);
        cppMap.emplace(strKey, cppValue);
    }
    return cppMap;
}
// exposed to python
void StoredValues::setAttr(
    const std::string &name,
    const boost::python::object &value
) {
    this->dict[name.c_str()] = value;
}
boost::python::object StoredValues::getAttr(
    const StoredValues &self,
    const std::string &name
) {
    boost::python::object value;
    try {
        value = self.dict.get(name.c_str(),value);
    } catch(const std::exception &e) {
        std::string errorMsg = e.what();
        errorMsg += "Value Does Exists";
        PyErr_SetString(
            PyExc_AttributeError, errorMsg.c_str()
        );
        boost::python::throw_error_already_set();
    }
    return value;
}
boost::python::dict StoredValues::getValuesDict() const {
    return this->dict;
}
boost::python::object StoredValues::get(
    const std::string &key,
    const boost::python::object &defaultValue
) const {
    boost::python::object object;
    object = this->dict.get(key.c_str(),defaultValue);
    return object;
}
void StoredValues::delItem(const std::string &key) {
    if (this->dict.has_key(key.c_str())) {
        this->dict.attr("__delitem__")(key.c_str());
    }
}
}