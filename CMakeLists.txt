cmake_minimum_required(VERSION 3.17)
project(WCasm C)

include_directories(".")
#include_directories("./include/*")
include_directories("./cmd/wcasm-objdump/include")

set(CMAKE_C_STANDARD 99)

add_executable(WCasm main.c
        tool/leb128/leb128.c
        wasm/wasm_reader/wasm_reader.c wasm/wasm_reader/segment.c
        wasm/module.c
        cmd/wcasm-objdump/dump.c cmd/wcasm-objdump/print.c
        include/wasm/op_code.h wasm/op_code.c wasm/instruction/instruction.c include/wasm/instruction/instruction.h tool/vector/vector.c include/tool/vector/vector.h)