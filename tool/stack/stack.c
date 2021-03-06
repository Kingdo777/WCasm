#include <string.h>
#include <include/tool/error/error_handle.h>
#include "include/tool/stack/stack.h"

void initStack(stack *s) {
    s->cap = STACK_INIT_SIZE;
    s->size = 0;
    s->bp = malloc(s->cap * STACK_ELE_SIZE);
    s->sp = s->bp;
}

void freeStack(stack *s) {
    if (s->cap > 0 && s->bp != NULL) {
        free(s->bp);
    }
}

uint64 get_stack_size(stack *s) {
    return s->size;
}

uint64 get_top_stack_ele(stack *s) {
    return *(s->sp - 1);
}

uint64 *get_top_stack_ele_p(stack *s) {
    return s->sp - 1;
}

void copy_val(stack *s, uint64 dest, uint64 src, uint64 count) {
    for (uint64 i = 0; i < count; ++i) {
        s->bp[dest + i] = s->bp[src + i];
    }
}

void push_val(stack *s, uint64 val) {
    if ((get_stack_size(s) + 1) > s->cap) {
        s->cap += STACK_INIT_SIZE;
        void *old_bp = s->bp;
        s->bp = malloc(s->cap * STACK_ELE_SIZE);
        memcpy(s->bp, old_bp, get_stack_size(s) * STACK_ELE_SIZE);
        s->sp = s->bp + get_stack_size(s);
        free(old_bp);
    }
    *(s->sp) = val;
    s->sp++;
    s->size++;
}

uint64 pop_val(stack *s) {
    s->sp--;
    s->size--;
    if (s->sp < s->bp) {
        errorExit("stack overflow\n");
    } else {
        return *s->sp;
    }
}

void pushS32(stack *s, int32 val) {
    PUSH(s, val);
}

void pushU32(stack *s, uint32 val) {
    PUSH(s, val);
}

void pushS64(stack *s, int64 val) {
    PUSH(s, val);
}

void pushU64(stack *s, uint64 val) {
    PUSH(s, val);
}

void pushF32(stack *s, float32 val) {
    uint32 val_f32 = *(uint32 *) &val;
    PUSH(s, val_f32);
}

void pushF64(stack *s, float64 val) {
    uint64 val_f64 = *(uint64 *) &val;
    PUSH(s, val_f64);
}

void pushByte(stack *s, byte val) {
    PUSH(s, val);
}

void pushBool(stack *s, bool val) {
    PUSH(s, val);
}

int32 popS32(stack *s) {
    return POP(s, int32);
}

uint32 popU32(stack *s) {
    return POP(s, uint32);
}

int64 popS64(stack *s) {
    return POP(s, int64);
}

uint64 popU64(stack *s) {
    return POP(s, uint64);
}

float32 popF32(stack *s) {
    uint32 val_f32 = POP(s, uint32);
    return *(float32 *) &val_f32;
}

float64 popF64(stack *s) {
    uint64 val_f64 = POP(s, uint64);
    return *(float64 *) &val_f64;
}

byte popByte(stack *s) {
    return POP(s, byte);
}

bool popBool(stack *s) {
    return POP(s, bool);
}