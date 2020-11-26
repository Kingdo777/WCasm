//
// Created by kingdo on 2020/11/26.
//

#include <include/wasm/vm/vm.h>

void i32Eqz_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s));
    v->pc.ip++;
}

void i64Eqz_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s));
    v->pc.ip++;
}