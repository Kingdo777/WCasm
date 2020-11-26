#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "include/tool/stack/stack.h"

void initStack(stack *s) {
    s->cap = STACK_INIT_SIZE;
    s->bp = malloc(s->cap);
    s->sp = s->bp;
}

uint64 get_stack_size(stack *s) {
    return (uint64) (s->sp - s->bp);
}

void push(stack *s, void *val_addr, uint32 val_size) {
    if ((get_stack_size(s) + val_size) > s->cap) {
        s->cap += ((val_size / STACK_INIT_SIZE + 1) * STACK_INIT_SIZE);
        void *old_bp = s->bp;
        s->bp = malloc(s->cap);
        memcpy(s->bp, old_bp, get_stack_size(s));
        s->sp = s->bp + get_stack_size(s);
        free(old_bp);
    }
    memcpy(s->sp, val_addr, val_size);
    s->sp += val_size;
}

void pop(stack *s, void *val_addr, uint32 val_size) {
    s->sp -= val_size;
    if (s->sp < s->bp) {
        fprintf(stderr, "stack overflow\n");
        exit(0);
    } else {
        memcpy(val_addr, s->sp, val_size);
    }
}

void pushS32(stack *s, int32 val) {
    push(s, &val, sizeof(int32));
}

void pushU32(stack *s, uint32 val) {
    push(s, &val, sizeof(uint32));
}

void pushS64(stack *s, int64 val) {
    push(s, &val, sizeof(int64));
}

void pushU64(stack *s, uint64 val) {
    push(s, &val, sizeof(uint64));
}

void pushF32(stack *s, float32 val) {
    push(s, &val, sizeof(float32));
}

void pushF64(stack *s, float64 val) {
    push(s, &val, sizeof(float64));
}

void pushByte(stack *s, byte buf) {
    push(s, &buf, 1);
}

void pushNByte(stack *s, byte *buf, uint64 N) {
    push(s, buf, N);
}

void pushBool(stack *s, uint32 b) {
    pushU32(s, (uint32) b);
}


int32 popS32(stack *s) {
    int32 val;
    pop(s, &val, sizeof(int32));
    return val;
}

uint32 popU32(stack *s) {
    uint32 val;
    pop(s, &val, sizeof(uint32));
    return val;
}

uint32 popS64(stack *s) {
    uint32 val;
    pop(s, &val, sizeof(int64));
    return val;
}

uint32 popU64(stack *s) {
    uint32 val;
    pop(s, &val, sizeof(uint64));
    return val;
}

float32 popF32(stack *s) {
    float32 val;
    pop(s, &val, sizeof(float32));
    return val;
}

float64 popF64(stack *s) {
    float64 val;
    pop(s, &val, sizeof(float64));
    return val;
}

byte popByte(stack *s) {
    byte buf;
    pop(s, &buf, 1);
    return buf;
}

void popNByte(stack *s, byte *buf, uint64 N) {
    pop(s, buf, N);
}

uint32 popBool(stack *s) {
    uint32 b = popU32(s);
    return b;
}