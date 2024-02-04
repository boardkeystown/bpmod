#pragma once
namespace bpmod::writer {
enum class FileState {
    HEADER,
    LINES,
    TAIL
};
}