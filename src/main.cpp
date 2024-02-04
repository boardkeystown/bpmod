#include <iostream>
#include "pyscriptcaller/pyscriptcaller.hpp"

int main() {
    PyScriptCaller psc;
    psc.setFuncName("run_func");
    psc.setScript("./pyscripts/m.py");
    for (std::size_t i = 0; i < 5; ++i) {
        psc.run();
    }
    return 0;
}