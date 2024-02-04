#pragma once
#define BOOST_NO_AUTO_PTR
#include <boost/python.hpp>

enum class PSC_STATE {
    SETUP,
    RUN,
    ERROR
};

class PyScriptCaller {
private:
    std::string script_path;
    std::string func_name;
private:
    boost::python::object main_module;
    boost::python::dict main_namespace;
    boost::python::object run_func;
private:
    PSC_STATE state;
private:
    void errorCatch();
    void setup();
    void runFunc();
public:
    PyScriptCaller();
    ~PyScriptCaller();
    void setScript(const std::string &script_path);
    void setFuncName(const std::string &func_name);
    void run();
};