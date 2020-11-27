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

void call_op(vm *v, instruction *inst) {
    func_index f_index = *(callArgs *) inst->arg;
    type_index t_index = *(type_index *) (v->m->func_sec.func_segment_addr + f_index);
    func_type bt = *(func_type *) (v->m->type_sec.type_segment_addr + t_index);
}