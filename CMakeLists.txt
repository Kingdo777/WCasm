cmake_minimum_required(VERSION 3.17)
project(WCasm C)

include_directories(".")
include_directories("./include")

set(CMAKE_C_STANDARD 99)

add_executable(WCasm main.c
        tool/leb128/leb128.c
        wasm/wasm_reader/wasm_reader.c
        wasm/wasm_reader/segment.c wasm/module.c)