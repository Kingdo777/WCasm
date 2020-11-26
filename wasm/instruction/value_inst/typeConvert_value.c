//
// Created by kingdo on 2020/11/26.
//

#include <math.h>
#include "include/wasm/vm/vm.h"

void i32wrapI64_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, (uint32) (popU64(s)));
    v->pc.ip++;
}

void i64ExtendI32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) (popS32(s)));
    v->pc.ip++;
}

void i64ExtendI32U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, (uint64) (popU32(s)));
    v->pc.ip++;
}

void f32ConvertI32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, (float32) (popS32(s)));
    v->pc.ip++;
}

void f32ConvertI32U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, (float32) (popU32(s)));
    v->pc.ip++;
}

void f32ConvertI64S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, (float32) (popS64(s)));
    v->pc.ip++;
}

void f32ConvertI64U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, (float32) (popU64(s)));
    v->pc.ip++;
}

void f32DemoteF64_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, (float32) (popF64(s)));
    v->pc.ip++;
}

void f64ConvertI32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, (float64) (popS32(s)));
    v->pc.ip++;
}

void f64ConvertI32U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, (float64) (popU32(s)));
    v->pc.ip++;
}

void f64ConvertI64S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, (float64) (popS64(s)));
    v->pc.ip++;
}

void f64ConvertI64U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, (float64) (popU64(s)));
    v->pc.ip++;
}

void f64PromoteF32_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, (float64) (popF32(s)));
    v->pc.ip++;
}

void i32Extend8S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, (int32) ((int8_t) (popS32(s))));
    v->pc.ip++;
}

void i32Extend16S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, (int32) ((int16_t) (popS32(s))));
    v->pc.ip++;
}

void i64Extend8S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) ((int8_t) (popS64(s))));
    v->pc.ip++;
}

void i64Extend16S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) ((int16_t) (popS64(s))));
    v->pc.ip++;
}

void i64Extend32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) ((int32_t) (popS64(s))));
    v->pc.ip++;
}

void i32ReinterpretF32_op(vm *v, instruction *inst) {
    v->pc.ip++;
}

void i64ReinterpretF64_op(vm *v, instruction *inst) {
    v->pc.ip++;
}

void f32ReinterpretI32_op(vm *v, instruction *inst) {
    v->pc.ip++;
}

void f64ReinterpretI64_op(vm *v, instruction *inst) {
    v->pc.ip++;
}

void i32TruncF32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, (int32) (trunc((float64) popF32(s))));
    v->pc.ip++;
}

void i32TruncF32U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, (uint32) (trunc((float64) popF32(s))));
    v->pc.ip++;
}

void i32TruncF64S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, (int32) (trunc(popF64(s))));
    v->pc.ip++;
}

void i32TruncF64U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, (uint32) (trunc(popF64(s))));
    v->pc.ip++;
}

void i64TruncF32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) (trunc((float64) popF32(s))));
    v->pc.ip++;
}

void i64TruncF32U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, (uint64) (trunc((float64) popF32(s))));
    v->pc.ip++;
}

void i64TruncF64S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) (trunc(popF64(s))));
    v->pc.ip++;
}

void i64TruncF64U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, (uint64) (trunc(popF64(s))));
    v->pc.ip++;
}

void truncSat_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    byte op = *(byte *) (inst->arg);
    switch (op) {
        case 0x00:
            pushS32(s, (int32) (trunc((float64) popF32(s))));
            break;
        case 0x01:
            pushU32(s, (uint32) (trunc((float64) popF32(s))));
            break;
        case 0x02:
            pushS32(s, (int32) (trunc(popF64(s))));
            break;
        case 0x03:
            pushU32(s, (uint32) (trunc(popF64(s))));
            break;
        case 0x04:
            pushS64(s, (int64) (trunc((float64) popF32(s))));
            break;
        case 0x05:
            pushU64(s, (uint64) (trunc((float64) popF32(s))));
            break;
        case 0x06:
            pushS64(s, (int64) (trunc(popF64(s))));
            break;
        case 0x07:
            pushU64(s, (uint64) (trunc(popF64(s))));
            break;
        default:
            break;
    }
    v->pc.ip++;
}