//
// Created by kingdo on 2020/11/26.
//

#include <include/wasm/vm/vm.h>
#include <math.h>

/*算法:https://blog.csdn.net/hitwhylz/article/details/10122617*/
const uint64 m1 = 0x5555555555555555; //binary: 0101...
const uint64 m2 = 0x3333333333333333; //binary: 00110011..
const uint64 m4 = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64 h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...
int popcount_3(uint64 x) {
    x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
    x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits
    x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits
    return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ...
}

void i32Clz_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val = popU32(s);
    uint32 count = sizeof(uint32) * 8;
    while (val != 0) {
        val >>= 1;
        count--;
    }
    pushU32(s, count);
}

void i32Ctz_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val = popU32(s);
    uint32 count = sizeof(uint32) * 8;
    while (val != 0) {
        val <<= 1;
        count--;
    }
    pushU32(s, count);
}

void i32Popcnt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 val = popU32(s);
    pushU32(s, (uint32) popcount_3((uint64) val));
    
}

void i64Clz_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val = popU64(s);
    uint64 count = sizeof(uint64) * 8;
    while (val != 0) {
        val >>= 1;
        count--;
    }
    pushU64(s, count);
}

void i64Ctz_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val = popU64(s);
    uint64 count = sizeof(uint64) * 8;
    while (val != 0) {
        val <<= 1;
        count--;
    }
    pushU64(s, count);
}

void i64Popcnt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint64 val = popU64(s);
    pushU64(s, (uint64) popcount_3((uint64) val));
}

void f32Abs_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, fabsf(popF32(s)));
}

void f32Neg_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, -popF32(s));
}

void f32Ceil_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, ceilf(popF32(s)));
}

void f32Floor_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, floorf(popF32(s)));
}

void f32Trunc_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, truncf(popF32(s)));
}

void f32Nearest_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF32(s, nearbyintf(popF32(s)));
}

void f32Sqrt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float32 f = popF32(s);
    pushF32(s, sqrtf(f));
}

void f64Abs_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, fabs(popF64(s)));
}

void f64Neg_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, -popF64(s));
}

void f64Ceil_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, ceil(popF64(s)));
}

void f64Floor_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, floor(popF64(s)));
}

void f64Trunc_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, trunc(popF64(s)));
}

void f64Nearest_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushF64(s, nearbyint(popF64(s)));
}

void f64Sqrt_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    float64 f = popF64(s);
    pushF64(s, sqrt(f));
}