//
// Created by kingdo on 2020/11/26.
//

#ifndef WCASM_STACK_H
#define WCASM_STACK_H

#include "include/tool/type.h"

#define STACK_INIT_SIZE 16*64 /*16个8字节*/
#define STACK_EXPAND_LENGTH 8*64 /*16个8字节*/

typedef struct stack {
    uint64 cap;
    void *sp;
    void *bp;
} stack;

void initStack(stack *s);

void freeStack(stack *s);

uint64 get_stack_size(stack *s);

void push(stack *s, void *val_addr, uint32 val_size);

void pop(stack *s, void *val_addr, uint32 val_size);

void pushS32(stack *s, int32 val);

void pushU32(stack *s, uint32 val);

void pushS64(stack *s, int64 val);

void pushU64(stack *s, uint64 val);

void pushF32(stack *s, float32 val);

void pushF64(stack *s, float64 val);

void pushByte(stack *s, byte buf);

void pushNByte(stack *s, byte *buf, uint64 N);

void pushBool(stack *s, uint32 b);

int32 popS32(stack *s);

uint32 popU32(stack *s);

uint32 popS64(stack *s);

uint32 popU64(stack *s);

float32 popF32(stack *s);

float64 popF64(stack *s);

byte popByte(stack *s);

void popNByte(stack *s, byte *buf, uint64 N);

uint32 popBool(stack *s);

#endif //WCASM_STACK_H
