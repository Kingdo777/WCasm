//
// Created by kingdo on 2020/11/26.
//

#include <include/wasm/vm/vm.h>

void i32Const_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, *(int32 *) inst->arg);
    v->pc.ip++;
}

void i64Const_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, *(int64 *) inst->arg);
    v->pc.ip++;
}

void f32Const_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, *(float32 *) inst->arg);
    v->pc.ip++;
}

void f64Const_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, *(float64 *) inst->arg);
    v->pc.ip++;
}
