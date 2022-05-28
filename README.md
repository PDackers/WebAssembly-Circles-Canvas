# WebAssembly-Circles-Canvas
Getting started with WebAssembly and Emscripten

## Tools used
* https://esmbly.github.io/WebAssemblyStudio/
* https://wasdk.github.io/WasmFiddle/
* https://emscripten.org/
* https://yarnpkg.com/
* https://yarnpkg.com/package/express

## Compiler options
emcc name.c -s WASM=1 -s EXPORTED_FUNCTIONS="['_fn1', '_main']" -o ../public/name.js

## Goal
My goal was to learn how to use JavaScript with WebAssembly and vice versa. I wanted to know how to export functions from C to JavaScript and how to use JavaScript within C.

## Project
120 circles bounce inside a canvas object. All circles have random colors and sizes, written in C and JavaScript.

## Course
This is the course on Udemy: https://www.udemy.com/course/webassembly-emscripten/. This excellent course with clear instructions taught me a lot about WebAssembly and why Emscripten is so powerful.
