#include "filestream.hpp"
namespace bpmod::writer {
FileStream::FileStream(
    const std::string &fpath
) {
    this->out.open(fpath.c_str());
}
FileStream::~FileStream() {
    if (this->out.is_open()) {
        this->out.close();
    }
}
FileStream& FileStream::operator<<(const int value) {
    this->out << value;
    return *this;
}
FileStream& FileStream::operator<<(const float value) {
    this->out << value;
    return *this;
}
FileStream& FileStream::operator<<(const double value) {
    this->out << value;
    return *this;
}
FileStream& FileStream::operator<<(const std::string &str) {
    this->out << str;
    return *this;
}
}