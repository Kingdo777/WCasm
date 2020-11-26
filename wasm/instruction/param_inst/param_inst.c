//
// Created by kingdo on 2020/11/26.
//

#include <include/wasm/vm/vm.h>

void drop_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    popU64(s);
    v->pc.ip++;
}

void select_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    if (popBool(s)) {
        popU64(s);
    } else {
        uint64 a = popU64(s);
        popU64(s);
        pushU64(s, a);
    }
    v->pc.ip++;
}