#include "pyscriptcaller.hpp"

#include "pyscriptcallerexception.hpp"

#include <iostream>
#include <boost/filesystem.hpp>

// private 
void PyScriptCaller::errorCatch() {
    // Just get the exception text!
    // *should catch any posable error!
    PyObject* ptype = nullptr;
    PyObject* pvalue = nullptr;
    PyObject* ptraceback = nullptr;
    PyErr_Fetch(&ptype, &pvalue, &ptraceback);
    PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);
    if (ptraceback != nullptr) {
        PyException_SetTraceback(pvalue, ptraceback);
    }
    boost::python::handle<> htype(ptype);
    boost::python::handle<> hvalue(boost::python::allow_null(pvalue));
    boost::python::handle<> htraceback(boost::python::allow_null(ptraceback));
    boost::python::object traceback = boost::python::import("traceback");
    boost::python::object format_exception = traceback.attr("format_exception");
    boost::python::object formatted_list = format_exception(htype, hvalue, htraceback);
    boost::python::object formatted = boost::python::str("\n").join(formatted_list);
    std::string result_str = boost::python::extract<std::string>(formatted);
    std::cout << result_str << std::endl;
}
void PyScriptCaller::setup() {
    try {
        if (Py_IsInitialized()==0) Py_Initialize();
        boost::python::object none;
        this->main_module=boost::python::import("__main__");
        this->main_namespace=boost::python::dict(
            this->main_module.attr("__dict__")
        );
        boost::python::import("sys");
        boost::python::exec(
            "import sys\n"
            "sys.path.append('./')\n"
            "print('wow gang gang')",
            this->main_namespace);
        boost::python::exec_file(
            this->script_path.c_str(),
            this->main_namespace
        );
        this->run_func = this->main_namespace.get(
            this->func_name.c_str(),
            none
        );
        if (this->run_func.is_none()) {
            throw PyScriptCallerException(
                "Error: failed to bind method " + 
                this->func_name +
                "\n"
            );
        }
        this->state = PSC_STATE::RUN;
    }
    catch (const PyScriptCallerException &e) {
        std::cout << e.what();
    }
    catch(const boost::python::error_already_set &) {
        errorCatch();
    }
}
void PyScriptCaller::runFunc() {
    try {
        this->run_func();
    } catch(const boost::python::error_already_set &) {
        errorCatch();
    }
}
// public
PyScriptCaller::PyScriptCaller() {
    this->state = PSC_STATE::SETUP;
}
PyScriptCaller::~PyScriptCaller() {
    if (this->state== PSC_STATE::RUN) {
        this->run_func = boost::python::object();
        this->main_namespace.clear();
        this->main_module = boost::python::object();
    }
}
void PyScriptCaller::setScript(const std::string &script_path) {
    this->script_path = script_path;
}
void PyScriptCaller::setFuncName(const std::string &func_name) {
    this->func_name = func_name;
}
void PyScriptCaller::run() {
    if (!boost::filesystem::exists(this->script_path)) {
        std::cout << "File does not exists!" 
                  << this->script_path
                  << "\n";
        return;
    }
    switch (this->state) {
        case PSC_STATE::SETUP:
            this->setup();
            break;
        case PSC_STATE::RUN:
            this->runFunc();
            break;
        default:
            break;
    }
}