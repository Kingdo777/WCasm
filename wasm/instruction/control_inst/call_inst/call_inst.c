//
// Created by kingdo on 2020/11/27.
//

#include <include/wasm/module.h>
#include <include/tool/stack/stack.h>
#include <include/wasm/vm/vm.h>

uint32 get_import_func_count(module *m) {
    uint32 count = 0;
    for (uint32 i = 0; i < m->import_sec.import_segment_count; i++) {
        if (m->import_sec.import_segment_addr->im_desc.tag == func_im_export_tag)
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
            .pc = 0
    };
    push_control_stack(&v->controlStack, cf);
}

void exitBlock(vm *v) {
    struct control_frame cf = pop_control_stack(&v->controlStack);
    for (int i = 0; i < cf.block_type.return_count; ++i) {
        v->operandStack.bp[cf.bp + i] = v->operandStack.bp[cf.bp + cf.block_type.param_count + i];
    }
    for (int i = 0; i < cf.block_type.param_count; ++i) {
        pop_control_stack(&v->controlStack);
    }
}

void callInternalFunc(vm *v, uint32 func_index) {
    type_index t_index = *(v->m->func_sec.func_segment_addr + func_index);
    func_type bt = *(v->m->type_sec.type_segment_addr + t_index);
    code *c = v->m->code_sec.code_segment_addr + func_index;
    enterBlock(v, Call, bt, &c->inst);
    uint32 localCount = 0;
    for (uint32 i = 0; i < c->local_var_info_count; ++i) {
        localCount += (c->lv_info + i)->count;
    }
    for (uint32 i = 0; i < localCount; i++) {
        pushU64(&v->operandStack, 0);
    }
}

void call_op(vm *v, instruction *inst) {
    func_index f_index = *(callArgs *) inst->arg;
    if (f_index < get_import_func_count(v->m)) {
        /*执行外部函数*/
    } else {
        callInternalFunc(v, f_index - get_import_func_count(v->m));
    }
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