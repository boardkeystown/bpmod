#pragma once
#include <fstream>
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
}