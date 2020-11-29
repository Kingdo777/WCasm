//
// Created by kingdo on 2020/11/27.
//

#include <include/wasm/module.h>
#include <include/tool/stack/stack.h>
#include <include/wasm/vm/vm.h>
#include <zconf.h>

uint32 get_import_func_count(module *m) {
    uint32 count = 0;
    for (uint32 i = 0; i < m->import_sec.import_segment_count; i++) {
        if ((m->import_sec.import_segment_addr + i)->im_desc.tag == func_im_export_tag)
            count++;
    }
    return count;
}

void enterBlock(vm *v, byte op_code, func_type bt, vec *instructions) {
    control_frame cf = {
            .opcode = op_code,
            .instructions = instructions,
            .block_type = bt,
            .bp = v->operandStack.size - bt.param_count,
            .pc = 0,
            .depth=0
    };
    if (cf.opcode == Block || cf.opcode == Loop || cf.opcode == If) {
        cf.depth = get_top_control_stack_ele_p(&v->controlStack)->depth + 1;
    }
    push_control_stack(&v->controlStack, cf);
}

void exitBlock(vm *v) {
    struct control_frame cf = pop_control_stack(&v->controlStack);
    uint64 len = v->operandStack.size - cf.bp - cf.block_type.return_count;
    copy_val(&v->operandStack, cf.bp, cf.bp + len, cf.block_type.return_count);
    for (uint64 i = 0; i < len; ++i) {
        pop_control_stack(&v->controlStack);
    }
}

void callInternalFunc(vm *v, function *f) {
    func_type bt = f->tp;
    code *c = f->code;
    enterBlock(v, Call, bt, &c->inst);
    uint32 localCount = 0;
    for (uint32 i = 0; i < c->local_var_info_count; ++i) {
        localCount += (c->lv_info + i)->count;
    }
    for (uint32 i = 0; i < localCount; i++) {
        pushU64(&v->operandStack, 0);
    }
}

void callExternalFunc(vm *v, function *f) {
    stack pr_stack;
    initStack(&pr_stack);
    for (int i = 0; i < f->tp.param_count; ++i) {
        pushU64(&pr_stack, popU64(&v->operandStack));
    }
    f->native(&pr_stack);
    for (int i = 0; i < f->tp.return_count; ++i) {
        pushU64(&v->operandStack, popU64(&pr_stack));
    }
    freeStack(&pr_stack);
}

void execFunc(vm *v, function_index func_index) {
    function *f = (function *) v->func.get_ele(&v->func, func_index);
    if (NULL == f->native) {
        callInternalFunc(v, f);
    } else {
        callExternalFunc(v, f);
    }
}

void call_op(vm *v, instruction *inst) {
    function_index f_index = *(callArgs *) inst->arg;
    execFunc(v, f_index);
}

void callIndirect_op(vm *v, instruction *inst) {
    uint32 index = ((call_indirectArgs *) inst->arg)->index;
    function_index f_index = *(v->table.item + index);
    execFunc(v, f_index);
}

void localGet_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    control_stack *cs = &v->controlStack;
    uint32 index = *(uint32 *) inst->arg;
    uint64 val = s->bp[get_top_control_stack_ele_p(cs)->bp + index];
    pushU64(s, val);
}

void localSet_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    control_stack *cs = &v->controlStack;
    uint32 index = *(uint32 *) inst->arg;
    uint64 val = popU64(s);
    s->bp[get_top_control_stack_ele_p(cs)->bp + index] = val;
}

void localTee_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    control_stack *cs = &v->controlStack;
    uint32 index = *(uint32 *) inst->arg;
    s->bp[get_top_control_stack_ele_p(cs)->bp + index] = get_top_stack_ele(s);
}

void globalGet_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 index = *(uint32 *) inst->arg;
    uint64 val = v->globalVar[index];
    pushU64(s, val);
}

void globalSet_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    uint32 index = *(uint32 *) inst->arg;
    uint64 val = popU64(s);
    v->globalVar[index] = val;
}