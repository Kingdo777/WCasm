//
// Created by kingdo on 2020/11/27.
//

#include <include/wasm/vm/vm.h>
#include "include/tool/error/error_handle.h"

void memorySize_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, get_memoryCount(&v->memory));
}

void memoryGrow_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, grow_memory(&v->memory, popU32(s)));
}

byte read_U8(stack *s, vm *v, instruction *inst) {
    byte buf;
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (read_memory(&v->memory, offset, &buf, sizeof(byte))) {
        return buf;
    }
    errorExit("mem read wrong\n");
}

uint16_t read_U16(stack *s, vm *v, instruction *inst) {
    uint16_t buf;
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (read_memory(&v->memory, offset, (byte *) &buf, sizeof(uint16_t))) {
        return buf;
    }
    errorExit("mem read wrong\n");
}

uint32 read_U32(stack *s, vm *v, instruction *inst) {
    uint32 buf;
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (read_memory(&v->memory, offset, (byte *) &buf, sizeof(uint32))) {
        return buf;
    }
    errorExit("mem read wrong\n");
}

uint64 read_U64(stack *s, vm *v, instruction *inst) {
    uint64 buf;
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (read_memory(&v->memory, offset, (byte *) &buf, sizeof(uint64))) {
        return buf;
    }
    errorExit("mem read wrong\n");
}

void write_U8(stack *s, vm *v, instruction *inst, byte buf) {
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (!write_memory(&v->memory, offset, &buf, sizeof(byte))) {
        errorExit("mem write wrong\n");
    }

}

void write_U16(stack *s, vm *v, instruction *inst, uint16_t buf) {
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (!write_memory(&v->memory, offset, (byte *) &buf, sizeof(uint16_t))) {
        errorExit("mem write wrong\n");
    }

}

void write_U32(stack *s, vm *v, instruction *inst, uint32 buf) {
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (!write_memory(&v->memory, offset, (byte *) &buf, sizeof(uint32))) {
        errorExit("mem write wrong\n");
    }
}

void write_U64(stack *s, vm *v, instruction *inst, uint64 buf) {
    uint64 offset = ((memArgs *) inst->arg)->offset + popU64(s);
    if (!write_memory(&v->memory, offset, (byte *) &buf, sizeof(uint64))) {
        errorExit("mem write wrong\n");
    }
}

void i32Load_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, read_U32(s, v, inst));
}

void i64Load_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, read_U64(s, v, inst));
}

void f32Load_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, read_U32(s, v, inst));
}

void f64Load_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, read_U64(s, v, inst));
}

void i32Load8S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, (int32) (int8_t) read_U8(s, v, inst));
}

void i32Load8U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, (uint32) (uint8_t) read_U8(s, v, inst));
}

void i32Load16S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS32(s, (int32) (int16_t) read_U16(s, v, inst));
}

void i32Load16U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU32(s, (uint32) (uint16_t) read_U16(s, v, inst));
}

void i64Load8S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) (int8_t) read_U8(s, v, inst));
}

void i64Load8U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, (uint64) (uint8_t) read_U8(s, v, inst));
}

void i64Load16S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) (int16_t) read_U16(s, v, inst));
}

void i64Load16U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, (uint64) (uint16_t) read_U16(s,v, inst));
}

void i64Load32S_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushS64(s, (int64) (int32) read_U32(s, v, inst));
}

void i64Load32U_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    pushU64(s, (uint64) (uint32) read_U32(s, v, inst));
}

void i32Store_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U32(s, v, inst, popU32(s));
}

void i64Store_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U64(s, v, inst, popU64(s));
}

void f32Store_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U32(s, v, inst, popU32(s));
}

void f64Store_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U64(s, v, inst, popU64(s));
}

void i32Store8_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U8(s, v, inst, (uint8_t) popU32(s));
}

void i32Store16_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U16(s, v, inst, (uint16_t) popU32(s));
}

void i64Store8_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U8(s, v, inst, (uint8_t) popU64(s));
}

void i64Store16_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U16(s, v, inst, (uint16_t) popU64(s));
}

void i64Store32_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    write_U32(s, v, inst, (uint32) popU64(s));
}