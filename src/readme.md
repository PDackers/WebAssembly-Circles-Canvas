https://esmbly.github.io/WebAssemblyStudio/

https://wasdk.github.io/WasmFiddle/

emcc strings.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_getStr', '_main']" -o ../public/strings.js
