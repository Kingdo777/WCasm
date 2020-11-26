#include <include/wasm/vm/vm.h>
#include "include/wasm/wasm_reader/wasm_reader.h"
#include "cmd/wcasm-objdump/include/dump.h"


int main() {
    vm v = {};
    initStack(&v.operandStack);
    init_opNames();
    init_op();
    const char *filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/rust/examples/target/wasm32-unknown-unknown/release/ch01_hw.wasm";
    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/js/ch01_hw.wasm";
    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/js/ch01_hw.wasm";
    wasm_reader *wr = create_wasm_reader(&v.m, filename);
    wcasm_objdump(&v.m);
    destroy_wasm_reader(wr);
    return 0;
}
