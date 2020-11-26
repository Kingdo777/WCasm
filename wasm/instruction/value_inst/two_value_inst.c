//
// Created by kingdo on 2020/11/26.
//

#include <include/wasm/vm/vm.h>
#include <math.h>

void i32Add_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 + val1);
    v->pc.ip++;
}

void i32Sub_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 - val1);
    v->pc.ip++;
}

void i32Mul_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 * val1);
    v->pc.ip++;
}

void i32DivS_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    int32 val1 = popS32(s);
    int32 val2 = popS32(s);
    pushS32(s, val2 / val1);
    v->pc.ip++;
}

void i32DivU_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 / val1);
    v->pc.ip++;
}

void i32RemS_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    int32 val1 = popS32(s);
    int32 val2 = popS32(s);
    pushS32(s, val2 % val1);
    v->pc.ip++;
}

void i32RemU_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 % val1);
    v->pc.ip++;
}

void i32And_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 & val1);
    v->pc.ip++;
}

void i32Or_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 | val1);
    v->pc.ip++;
}

void i32Xor_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 ^ val1);
    v->pc.ip++;
}

void i32Shl_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 << (val1 % 32));
    v->pc.ip++;
}

void i32ShrS_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    int32 val2 = popS32(s);
    pushS32(s, val2 >> (val1 % 32));
    v->pc.ip++;
}

void i32ShrU_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s);
    uint32 val2 = popU32(s);
    pushU32(s, val2 >> (val1 % 32));
    v->pc.ip++;
}

void i32RotL_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s) % 32;
    uint32 val2 = popU32(s);
    pushU32(s, (val2 << val1) | (val2 >> (32 - val1)));
    v->pc.ip++;
}

void i32RotR_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val1 = popU32(s) % 32;
    uint32 val2 = popU32(s);
    pushU32(s, (val2 >> val1) | (val2 << (32 - val1)));
    v->pc.ip++;
}

void i64Add_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 + val1);
    v->pc.ip++;
}

void i64Sub_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 - val1);
    v->pc.ip++;
}

void i64Mul_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 * val1);
    v->pc.ip++;
}

void i64DivS_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    int64 val1 = popS64(s);
    int64 val2 = popS64(s);
    pushS64(s, val2 / val1);
    v->pc.ip++;
}

void i64DivU_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 / val1);
    v->pc.ip++;
}

void i64RemS_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    int64 val1 = popS64(s);
    int64 val2 = popS64(s);
    pushS64(s, val2 % val1);
    v->pc.ip++;
}

void i64RemU_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 % val1);
    v->pc.ip++;
}

void i64And_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 & val1);
    v->pc.ip++;
}

void i64Or_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 | val1);
    v->pc.ip++;
}

void i64Xor_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 ^ val1);
    v->pc.ip++;
}

void i64Shl_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 << (val1 % 64));
    v->pc.ip++;
}

void i64ShrS_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    int64 val2 = popS64(s);
    pushS64(s, val2 >> (val1 % 64));
    v->pc.ip++;
}

void i64ShrU_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s);
    uint64 val2 = popU64(s);
    pushU64(s, val2 >> (val1 % 64));
    v->pc.ip++;
}

void i64RotL_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s) % 64;
    uint64 val2 = popU64(s);
    pushU64(s, (val2 << val1) | (val2 >> (64 - val1)));
    v->pc.ip++;
}

void i64RotR_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val1 = popU64(s) % 64;
    uint64 val2 = popU64(s);
    pushU64(s, (val2 >> val1) | (val2 << (64 - val1)));
    v->pc.ip++;
}

void f32Add_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = popF32(s);
    pushF32(s, val2 + val1);
    v->pc.ip++;
}

void f32Sub_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = popF32(s);
    pushF32(s, val2 - val1);
    v->pc.ip++;
}

void f32mul_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = popF32(s);
    pushF32(s, val2 * val1);
    v->pc.ip++;
}

void f32Div_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = popF32(s);
    pushF32(s, val2 / val1);
    v->pc.ip++;
}

void f32min_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = popF32(s);
    pushF32(s, val2 < val1 ? val2 : val1);
    v->pc.ip++;
}

void f32Max_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = popF32(s);
    pushF32(s, val2 > val1 ? val2 : val1);
    v->pc.ip++;
}

void f32Copysign_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 val1 = popF32(s);
    float32 val2 = fabsf(popF32(s));
    pushF32(s, val1 > 0 ? val2 : -val2);
    v->pc.ip++;
}

void f64Add_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = popF64(s);
    pushF64(s, val2 + val1);
    v->pc.ip++;
}

void f64Sub_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = popF64(s);
    pushF64(s, val2 - val1);
    v->pc.ip++;
}

void f64mul_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = popF64(s);
    pushF64(s, val2 * val1);
    v->pc.ip++;
}

void f64Div_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = popF64(s);
    pushF64(s, val2 / val1);
    v->pc.ip++;
}

void f64min_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = popF64(s);
    pushF64(s, val2 < val1 ? val2 : val1);
    v->pc.ip++;
}

void f64Max_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = popF64(s);
    pushF64(s, val2 > val1 ? val2 : val1);
    v->pc.ip++;
}

void f64Copysign_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 val1 = popF64(s);
    float64 val2 = fabs(popF64(s));
    pushF64(s, val1 > 0 ? val2 : -val2);
    v->pc.ip++;
}
