#include "filewriter.hpp"
#include <algorithm>
namespace bpmod::writer {
// private
void FileWriter::addNewFile(const std::string &fileName) {
    auto file = this->filesMap.find(fileName);
    if (file == this->filesMap.end()) {
        this->filesMap.emplace(
            fileName,
            FileContainer(fileName)
        );
    }
}
void FileWriter::writeHeadLines(FileContainer &cur_file) {
    if (cur_file.state != FileState::HEADER) return;
    std::for_each(
        this->headerLines.begin(),
        this->headerLines.end(),
        [&cur_file](const auto &str) {
            *cur_file.fs << str << "\n";
        }
    );
    cur_file.state = FileState::LINES;
}
void FileWriter::writeTailLines(FileContainer &cur_file) {
    std::for_each(
        this->tailLines.begin(),
        this->tailLines.end(),
        [&cur_file](const auto &str) {
            *cur_file.fs << str << "\n";
        }
    );
}
void FileWriter::closeFiles() {
    for (auto &[name,file] : this->filesMap) {
        this->writeTailLines(file);
        file.fs->out << std::flush;
        file.fs->out.close();
    }
}
// public
FileWriter::FileWriter() :
    filesMap({}),
    headerLines({}),
    tailLines({})
{}
FileWriter::~FileWriter() {
    this->closeFiles();
}
void FileWriter::setHeaderLines(
    const std::vector<std::string> &headerLines
) {
    this->headerLines = headerLines;
}
void FileWriter::writeLine(
    const std::string &fileName,
    const std::string &line
) {
    this->addNewFile(fileName);
    auto file = this->filesMap.find(fileName);
    this->writeHeadLines(file->second);
    *file->second.fs << line << "\n";
}
void FileWriter::setTailLines(
    const std::vector<std::string> &tailLines
) {
    this->tailLines = tailLines;
}
} // namespace bpmod::writer
