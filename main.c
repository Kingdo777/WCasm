#include <include/wasm/vm/vm.h>
#include <include/tool/error/error_handle.h>
#include "include/wasm/wasm_reader/wasm_reader.h"
#include "cmd/wcasm-objdump/include/dump.h"

#define INIT_MAIN() do{ \
       init_opNames();  \
       init_op();       \
}while (0)

bool stack_test(vm *v);

int main() {
    INIT_MAIN();

    const char *filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/rust/examples/target/wasm32-unknown-unknown/release/ch01_hw.wasm";
    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/js/ch01_hw.wasm";
    filename = "/home/kingdo/go/src/github.com/Kingdo777/wasmgo-book/code/js/ch01_hw.wasm";

    vm *v = createVM();
    if (!stack_test(v)) {
        errorExit("stack op wrong\n");
    }
    wasm_reader *wr = createWasmReader();
    module *m = createModule(filename);

    decode_module(wr, m);
    wcasm_objdump(m);
    exec(v, m);

    free_module(wr, m);
    destroy_wasm_reader(wr);
    destroyVM(v);
    return 0;
}
