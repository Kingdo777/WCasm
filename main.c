#include "include/wasm/wasm_reader/wasm_reader.h"
#include "cmd/wcasm-objdump/include/dump.h"


int main() {
    module m = {};
    const char *filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/rust/examples/target/wasm32-unknown-unknown/release/ch01_hw.wasm";
    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/js/ch01_hw.wasm";
//    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/wat/ch03_eg1_num.wasm";
//    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/wat/ch03_eg2_var.wasm";
//    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/wat/ch03_eg3_mem.wasm";
//    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/wat/ch03_eg4_block.wasm";
//    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/wat/ch03_eg6_call.wasm";
    wasm_reader *wr = create_wasm_reader(&m, filename);
    wcasm_objdump(&m);
    destroy_wasm_reader(wr);
    return 0;
}
