#pragma once
#include <vector>
#include <string>
namespace bpmod::maker::data {
struct MakerData {
int number;
std::vector<int> values;
MakerData();
MakerData(const MakerData &o);
MakerData& operator=(const MakerData &o);
MakerData(MakerData &&o);
MakerData& operator=(MakerData &&o);
~MakerData();
bool operator==(const MakerData &o) const;
bool operator!=(const MakerData &o) const;
std::string __str__() const;
std::string __repr__() const;
};
} // bpmod::maker::data