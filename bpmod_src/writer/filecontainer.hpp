#pragma once
#include <string>
#include <fstream>
#include <memory>
#include "filestate.hpp"
namespace bpmod::writer {
struct FileStream {
    std::ofstream out;
    FileStream(const std::string &fpath);
    ~FileStream();
    FileStream& operator<<(const int value);
    FileStream& operator<<(const float value);
    FileStream& operator<<(const double value);
    FileStream& operator<<(const std::string &str);
};

struct FileContainer {
    std::shared_ptr<FileStream> fs;
    FileState state;
    FileContainer();
    FileContainer(const std::string &fpath);
    ~FileContainer();
};
} // namespace bpmod::writer
