#include "store.hpp"
#include <vector>
#include "utils/pyListStrToVector.hpp"
#include "convert/sdtypesmaptocppvecstr.hpp"
#include "convert/pytocpptype.hpp"
#include "convert/sdtypetostr.hpp"
#include <string>
#include <iostream>
namespace bpmod::writer {
Store::Store() {}
Store::~Store() {
    auto valuesMap = this->storedValues.getValues();
    if (valuesMap.size()) {
        auto vecStr = convert::SDtypesMapToCppVecStr(valuesMap);
        this->fileWriter.setTailLines(vecStr);
    }
}
void Store::setHeaderLines(
    boost::python::list headLines
) {
    std::vector<std::string> vec = utils::pyListStrToVector(headLines);
    this->fileWriter.setHeaderLines(vec);
}
void Store::writeLine(
    boost::python::str fileName,
    boost::python::str line
) {
    this->fileWriter.writeLine(
        boost::python::extract<std::string>(fileName),
        boost::python::extract<std::string>(line)
    );
}
boost::python::object Store::writeArguments(
    const boost::python::tuple &args,
    const boost::python::dict &kwargs
) {
    Store *self = nullptr;
    std::string output_file {""};
    std::string args_str {""};
    for (boost::python::ssize_t i = 0; i < boost::python::len(args); i++) {
        if (i == 0) {
            self = boost::python::extract<Store*>(args[0]);
            continue;
        }
        auto value = convert::PyToCppType(args[i]);
        args_str += convert::SdTypeToStr(value);
        if (i < boost::python::len(args)-1) {
            args_str += ",";
        }
    }
    boost::python::list keys = kwargs.keys();
    for (boost::python::ssize_t i = 0; i < boost::python::len(keys); ++i) {
        boost::python::object key = keys[i];
        std::string keyCpp = boost::python::extract<std::string>(key);
        boost::python::object value = kwargs[key];
        // get the output file provided
        if (keyCpp == "F" || keyCpp == "file") {
            output_file = boost::python::extract<std::string>(value);
        }
    }
    self->fileWriter.writeLine(
        output_file,
        args_str
    );
    // do we really need to return a none object!? Ok...
    return boost::python::object();
}
void Store::setTailLines(
    boost::python::list headLines
) {
    std::vector<std::string> vec = utils::pyListStrToVector(headLines);
    this->fileWriter.setTailLines(vec);
}
} // namespace bpmod::writer
