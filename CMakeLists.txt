cmake_minimum_required(VERSION 3.17)
project(WCasm C)
include_directories(".")
include_directories("./include")
include_directories("./cmd/wcasm-objdump/include")

set(CMAKE_C_STANDARD 99)

add_executable(WCasm main.c
        tool/leb128/leb128.c
        wasm/wasm_reader/wasm_reader.c
        include/wasm/wasm_reader/wasm_reader.h
        wasm/wasm_reader/segment.c
        wasm/module.c
        cmd/wcasm-objdump/dump.c cmd/wcasm-objdump/print.c
        include/wasm/op_code.h wasm/op_code.c
        wasm/instruction/instruction.c include/wasm/instruction/instruction.h
        tool/vector/vector.c include/tool/vector/vector.h
        tool/stack/stack.c tool/stack/control_stack.c include/tool/stack/stack.h
        wasm/vm/vm.c include/wasm/vm/vm.h
        wasm/instruction/param_inst/param_inst.c wasm/instruction/value_inst/const_value_inst.c wasm/instruction/value_inst/test_value_inst.c wasm/instruction/value_inst/compare_value_inst.c wasm/instruction/value_inst/one_valus_inst.c wasm/instruction/value_inst/two_value_inst.c wasm/instruction/value_inst/typeConvert_value.c wasm/vm/memory.c wasm/instruction/mem_inst/mem_inst.c include/tool/error/error_handle.h tool/stack/stack_test.c wasm/instruction/control_inst/call_inst/call_inst.c wasm/instruction/control_inst/block_inst/block_inst.c)
target_link_libraries(WCasm m)
