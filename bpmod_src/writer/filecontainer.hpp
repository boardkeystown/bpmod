#pragma once
#include <string>
#include <memory>
#include "filestate.hpp"
#include "filestream.hpp"
namespace bpmod::writer {
struct FileContainer {
    std::shared_ptr<FileStream> fs;
    FileState state;
    FileContainer();
    FileContainer(const std::string &fpath);
    ~FileContainer();
};
} // namespace bpmod::writer
