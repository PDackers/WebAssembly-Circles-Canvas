#include <emscripten.h>
#include <stdio.h>

char * strVal = "My string variable";

char * getStr() {
    return strVal;
}

int main() {
    printf("WASM Ready.\n");
    return 1;
}
