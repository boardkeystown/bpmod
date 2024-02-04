#include <stdexcept>
#include <string>
class PyScriptCallerException : public std::runtime_error {
public:
    PyScriptCallerException(const std::string& msg)
        : std::runtime_error(msg) {}
};