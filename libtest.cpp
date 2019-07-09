#include <iostream>
#include <iostream>
#include <cstdlib>


#include <emscripten.h>

#include <emscripten/threading.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

int myrun() {
    return 42;
}

EMSCRIPTEN_BINDINGS(viennatswasm) { emscripten::function("myrun", &myrun); }