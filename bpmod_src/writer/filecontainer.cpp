#include "filecontainer.hpp"
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


FileContainer::FileContainer() {
    this->state = FileState::HEADER;
}
FileContainer::FileContainer(
    const std::string &fpath
) {
    this->fs = std::make_shared<FileStream>(fpath);
    this->state = FileState::HEADER;
}
FileContainer::~FileContainer() {}
} // namespace bpmod::writer
