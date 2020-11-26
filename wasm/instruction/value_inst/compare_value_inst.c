//
// Created by kingdo on 2020/11/26.
//

#include <include/wasm/vm/vm.h>

/**
 * 需要注意:
 *   大于指的是,后弹出的比前面弹出的要大
 *   小于指的是,后弹出的比前面弹出的要小
 * 因此下面的函数中:
 *   Lt 对应 ">"  Gt 对应 "<"
 *   Le 对应 ">=" Gt 对应 "<="
 */
void i32Eq_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s) == popU32(s));
    v->pc.ip++;
}

void i32Ne_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s) != popU32(s));
    v->pc.ip++;
}

void i32Lts_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS32(s) > popS32(s));
    v->pc.ip++;
}

void i32Ltu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s) > popU32(s));
    v->pc.ip++;
}

void i32Gts_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS32(s) < popS32(s));
    v->pc.ip++;
}

void i32Gtu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s) < popU32(s));
    v->pc.ip++;
}

void i32Les_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS32(s) >= popS32(s));
    v->pc.ip++;
}

void i32Leu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s) >= popU32(s));
    v->pc.ip++;
}

void i32Ges_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS32(s) <= popS32(s));
    v->pc.ip++;
}

void i32Geu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU32(s) <= popU32(s));
    v->pc.ip++;
}

void i64Eq_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s) == popU64(s));
    v->pc.ip++;
}

void i64Ne_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s) != popU64(s));
    v->pc.ip++;
}

void i64Lts_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS64(s) > popS64(s));
    v->pc.ip++;
}

void i64Ltu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s) > popU64(s));
    v->pc.ip++;
}

void i64Gts_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS64(s) < popS64(s));
    v->pc.ip++;
}

void i64Gtu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s) < popU64(s));
    v->pc.ip++;
}

void i64Les_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS64(s) >= popS64(s));
    v->pc.ip++;
}

void i64Leu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s) >= popU64(s));
    v->pc.ip++;
}

void i64Ges_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popS64(s) <= popS64(s));
    v->pc.ip++;
}

void i64Geu_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popU64(s) <= popU64(s));
    v->pc.ip++;
}

void f32Eq_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF32(s) == popF32(s));
    v->pc.ip++;
}

void f32Ne_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF32(s) != popF32(s));
    v->pc.ip++;
}


void f32Lt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF32(s) > popF32(s));
    v->pc.ip++;
}


void f32Gt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF32(s) < popF32(s));
    v->pc.ip++;
}


void f32Le_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF32(s) >= popF32(s));
    v->pc.ip++;
}


void f32Ge_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF32(s) <= popF32(s));
    v->pc.ip++;
}

void f64Eq_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF64(s) == popF64(s));
    v->pc.ip++;
}

void f64Ne_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF64(s) != popF64(s));
    v->pc.ip++;
}


void f64Lt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF64(s) > popF64(s));
    v->pc.ip++;
}


void f64Gt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF64(s) < popF64(s));
    v->pc.ip++;
}


void f64Le_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF64(s) >= popF64(s));
    v->pc.ip++;
}


void f64Ge_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushBool(s, popF64(s) <= popF64(s));
    v->pc.ip++;
}