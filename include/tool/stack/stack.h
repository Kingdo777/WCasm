//
// Created by kingdo on 2020/11/26.
//

#ifndef WCASM_STACK_H
#define WCASM_STACK_H

#include "include/tool/type.h"

#define STACK_ELE_SIZE (8*8)
#define STACK_INIT_SIZE (64) /*64个8字节*/

#define PUSH(s, val) push_val(s, (uint64)val)
#define POP(s, type) (type)pop_val(s)

typedef struct stack {
    /**
     * 无论是什么数据类型进来,都是以8字节的空间来存放的
     * */
    uint64 cap;
    uint64 size;
    uint64 *sp;
    uint64 *bp;
} stack;

void initStack(stack *s);

void freeStack(stack *s);

uint64 get_stack_size(stack *s);

void pushS32(stack *s, int32 val);

void pushU32(stack *s, uint32 val);

void pushS64(stack *s, int64 val);

void pushU64(stack *s, uint64 val);

void pushF32(stack *s, float32 val);

void pushF64(stack *s, float64 val);

void pushByte(stack *s, byte buf);


void pushBool(stack *s, bool val);

int32 popS32(stack *s);

uint32 popU32(stack *s);

uint32 popS64(stack *s);

uint64 popU64(stack *s);

float32 popF32(stack *s);

float64 popF64(stack *s);

byte popByte(stack *s);

bool popBool(stack *s);

#endif //WCASM_STACK_H
