#include "include/wasm/wasm_reader/wasm_reader.h"
#include "cmd/wcasm-objdump/include/dump.h"


int main() {
    module m = {};
    const char *filename = "/home/kingdo/go/src/github.com/zxh0/wasmgo-book/code/rust/examples/target/wasm32-unknown-unknown/release/ch01_hw.wasm";
    wasm_reader *wr = create_wasm_reader(&m, filename);
    wcasm_objdump(&m);
    destroy_wasm_reader(wr);
    return 0;
}
