#include "makerdata.hpp"
namespace bpmod::maker::data {
MakerData::MakerData() :
    number(0),
    values({})
{}
MakerData::MakerData(const MakerData &o) {
    *this=o;
}
MakerData& MakerData::operator=(const MakerData &o) {
    this->number=o.number;
    this->values=o.values;
    return *this;
}
MakerData::MakerData(MakerData &&o) :
    number(std::move(o.number)),
    values(std::move(o.values))
{
    o.number=0;
    o.values.clear();
}
MakerData& MakerData::operator=(MakerData &&o) {
    if(this==&o) return *this;
    //clear this stuff
    this->number=0;
    this->values.clear();
    //move other into this
    this->number=std::move(o.number);
    this->values=std::move(o.values);
    //set to know state
    o.number=0;
    o.values.clear();
    return *this;
}
MakerData::~MakerData() {}
bool MakerData::operator==(const MakerData &o) const {
    return  (
                this->number==o.number &&
                this->values==o.values
            );
}
bool MakerData::operator!=(const MakerData &o) const {
    return  (
                this->number!=o.number &&
                this->values!=o.values
            );
}
std::string MakerData::__str__() const {
    std::string result("");
    result+="number="
          +std::to_string(this->number)
          +",";
    result+="values=[";
    for (std::size_t i=0;i<this->values.size();++i) {
        if (i==this->values.size()-1) {
            result+=std::to_string(this->values[i]);
        } else {
            result+=std::to_string(this->values[i])
                  +",";
        }
    }
    result+="]";
    return result;
}
std::string MakerData::__repr__() const {
    return this->__str__();
}

} // bpmod::maker::data