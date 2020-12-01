#include <string.h>
#include <include/tool/error/error_handle.h>
#include "include/tool/stack/stack.h"

void initControlStack(control_stack *s) {
    s->cap = CONTROL_STACK_INIT_SIZE;
    s->size = 0;
    s->bp = malloc(s->cap * CONTROL_STACK_ELE_SIZE);
    s->sp = s->bp;
}

void freeControlStack(control_stack *s) {
    if (s->cap > 0 && s->bp != NULL) {
        free(s->bp);
    }
}

uint64 get_control_stack_size(control_stack *s) {
    return s->size;
}

control_frame *get_top_control_stack_ele_p(control_stack *s) {
    return s->sp - 1;
}

control_frame *get_top_fun_control_stack_ele_p(control_stack *s) {
    control_frame *cf = NULL;
    for (int i = 0; i < s->size; ++i) {
        cf = s->sp - 1 - i;
        if (cf->depth == 0)
            break;
    }
    if (NULL == cf)
        errorExit("no have func control_frame\n");
    return cf;
}

control_frame get_top_control_stack_ele(control_stack *s) {
    return *(s->sp - 1);
}

void push_control_stack(control_stack *s, control_frame val) {
    if ((get_control_stack_size(s) + 1) > s->cap) {
        s->cap += CONTROL_STACK_INIT_SIZE;
        void *old_bp = s->bp;
        s->bp = malloc(s->cap * CONTROL_STACK_ELE_SIZE);
        memcpy(s->bp, old_bp, get_control_stack_size(s) * CONTROL_STACK_ELE_SIZE);
        s->sp = s->bp + get_control_stack_size(s);
        free(old_bp);
    }
    *(s->sp) = val;
    s->sp += 1;
    s->size++;
}

control_frame pop_control_stack(control_stack *s) {
    s->sp -= 1;
    s->size--;
    if (s->sp < s->bp) {
        errorExit("control_stack overflow\n");
    } else {
        return *s->sp;
    }
}