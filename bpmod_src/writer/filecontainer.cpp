#include "filecontainer.hpp"
namespace bpmod::writer {
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
