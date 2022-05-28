#include <emscripten.h>
#include <stdio.h>

// Declare a reusable JS function.
EM_JS(void, jsFunction, (int n), {
    console.log("Call from EM_JS: " + n);
});

int main() {
    printf("WASM Ready.\n");

    // Call JS function (eval).
    emscripten_run_script("console.log('Hello, from C.')");

    // Call JS function ASYNC (eval).
    emscripten_async_run_script("console.log('Hello, from C. ASYNC.')", 1000);

    // Get return value from JS - INT.
    int jsVal = emscripten_run_script_int("getNum()");
    printf("Value from JS: %d\n", jsVal);

    // Get return value from JS - STR.
    char * jsStr = emscripten_run_script_string("getStr()");
    printf("Value from JS: %s\n", jsStr);

    // Execute EM_JS.
    jsFunction(144);

    return 1;
}
