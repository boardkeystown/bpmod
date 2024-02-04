#pragma once
#include <map>
#include <string>
#include <vector>
#include "filecontainer.hpp"
namespace bpmod::writer {
class FileWriter {
private:
    std::map<std::string,FileContainer> filesMap;
    std::vector<std::string> headerLines;
    std::vector<std::string> tailLines;
private:
    void addNewFile(const std::string &fileName);
    void writeHeadLines(FileContainer &cur_file);
    void writeTailLines(FileContainer &cur_file);
    void closeFiles();
public:
    FileWriter();
    ~FileWriter();
    void setHeaderLines(const std::vector<std::string> &headerLines);
    void writeLine(
        const std::string &fileName,
        const std::string &line
    );
    void setTailLines(const std::vector<std::string> &tailLines);
};
} // namespace bpmod::writer
