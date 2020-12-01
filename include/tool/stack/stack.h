//
// Created by kingdo on 2020/11/26.
//

#ifndef WCASM_STACK_H
#define WCASM_STACK_H

#include <include/tool/vector/vector.h>
#include <include/wasm/wasm_reader/segment.h>
#include "include/tool/type.h"

#define STACK_ELE_SIZE (8*8)
#define STACK_INIT_SIZE (64) /*64个8字节*/

#define CONTROL_STACK_ELE_SIZE (sizeof(control_frame))
#define CONTROL_STACK_INIT_SIZE (16)

#define PUSH(s, val) push_val(s, (uint64)val)
#define POP(s, type) (type)pop_val(s)

typedef struct control_frame {
    byte opcode;/*block,call都可以创建*/
    vec *instructions;
    func_type block_type;/*记录返回值类型*/
    uint64 bp;/*栈帧开始的操作数栈的位置,指向了第一个参数*/
    uint64 pc;
    /*用于执行return操作,对于每一函数块,值为0*/
    labelIndex depth;
} control_frame;

typedef struct control_stack {
    uint64 cap;
    uint64 size;
    control_frame *sp;
    control_frame *bp;
} control_stack;

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

void initControlStack(control_stack *s);

void freeStack(stack *s);

void freeControlStack(control_stack *s);

uint64 get_stack_size(stack *s);

uint64 get_top_stack_ele(stack *s);

uint64 *get_top_stack_ele_p(stack *s);

void copy_val(stack *s, uint64 dest, uint64 src, uint64 count);

void push_val(stack *s, uint64 val);

uint64 get_control_stack_size(control_stack *s);

control_frame get_top_control_stack_ele(control_stack *s);

control_frame *get_top_control_stack_ele_p(control_stack *s);

control_frame *get_top_fun_control_stack_ele_p(control_stack *s);

void push_control_stack(control_stack *s, control_frame val);

control_frame pop_control_stack(control_stack *s);

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

int64 popS64(stack *s);

uint64 popU64(stack *s);

float32 popF32(stack *s);

float64 popF64(stack *s);

byte popByte(stack *s);

bool popBool(stack *s);

#endif //WCASM_STACK_H
