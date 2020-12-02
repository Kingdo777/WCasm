//
// Created by kingdo on 2020/11/28.
//

#include <include/wasm/wasm_reader/segment.h>
#include <include/wasm/vm/vm.h>
#include <zconf.h>
#include <include/tool/error/error_handle.h>

byte fiveBlockReturnType[] = {
        I32,
        I64,
        F32,
        F64
};

func_type get_block_type(vm *v, int32 bt) {
    struct func_type block_type = {
            .param_count=0,
            .return_count=1,
            .return_types=NULL,
            .param_types=NULL
    };
    if (bt < 0) {
        switch (bt) {
            case BlockTypeI32:
                block_type.param_types = &fiveBlockReturnType[0];
                break;
            case BlockTypeI64:
                block_type.param_types = &fiveBlockReturnType[1];
                break;
            case BlockTypeF32:
                block_type.param_types = &fiveBlockReturnType[2];
                break;
            case BlockTypeF64:
                block_type.param_types = &fiveBlockReturnType[3];
                break;
            default:
                block_type.return_count = 0;
                break;
        }
    } else {
        block_type = *(v->m->type_sec.type_segment_addr + bt);
    }
    return block_type;
}

void block_op(vm *v, instruction *inst) {
    blockArgs *ba = (blockArgs *) inst->arg;
    func_type bt = get_block_type(v, ba->blockType);
    enterBlock(v, Block, bt, &ba->instructions);
}

void loop_op(vm *v, instruction *inst) {
    blockArgs *ba = (blockArgs *) inst->arg;
    func_type bt = get_block_type(v, ba->blockType);
    enterBlock(v, Loop, bt, &ba->instructions);
}

void if_op(vm *v, instruction *inst) {
    ifArgs *ia = (ifArgs *) inst->arg;
    func_type bt = get_block_type(v, ia->blockType);
    bool if_true = popBool(&v->operandStack);
    if (if_true) {
        enterBlock(v, If, bt, &ia->instructions1);
    } else {
        enterBlock(v, If, bt, &ia->instructions2);
    }
}

void br(vm *v, labelIndex l_index) {
    control_stack *cs = &v->controlStack;
    for (int i = 0; i < l_index; ++i) {
        /*如果是函数的退出,需要把所有的非call的control_frame弹出*/
        pop_control_stack(cs);
    }
    control_frame *cf = get_top_control_stack_ele_p(cs);
    if (cf->opcode == Loop) {
        /*这里的逻辑不太好理解,这里是回到loop标签的初始状态,也就是需要重新设置参数,此时的新参数是操作数栈的栈顶,
         * 我们需要将此部分移动到参数的位置,同时将多余的栈数据弹出,方式类似于对返回值的处理*/
        uint64 len = v->operandStack.size - cf->bp - cf->block_type.param_count;
        /*与exitBlock唯一的不同在于最后一个参数*/
        copy_val(&v->operandStack, cf->bp, cf->bp + len, cf->block_type.param_count);
        for (uint64 i = 0; i < len; ++i) {
            popU64(&v->operandStack);
        }
        /*重置PC*/
        cf->pc = 0;
    } else if (cf->opcode == Block || cf->opcode == Loop || cf->opcode == Call) {
        exitBlock(v);
    } else {
        errorExit("unknown opcode\n");
    }
}

void br_op(vm *v, instruction *inst) {
    labelIndex l_index = *(labelIndex *) inst->arg;
    br(v, l_index);
}

void brIf_op(vm *v, instruction *inst) {
    if (popBool(&v->operandStack)) {
        br_op(v, inst);
    }
}

void brTable_op(vm *v, instruction *inst) {
    stack *s = &v->operandStack;
    brTableArgs *bta = (brTableArgs *) inst->arg;
    uint64 t_index = popU64(s);
    labelIndex l_index = bta->defaultLabels;
    if (t_index < bta->labelCount)
        l_index = *(bta->labels + t_index);
    br(v, l_index);
}

void return_op(vm *v, instruction *inst) {
    labelIndex l_index = get_top_control_stack_ele_p(&v->controlStack)->depth;
    br(v, l_index);
}

void unreachable_op(vm *v, instruction *inst) {
    errorExit("exec unreachable_op\n");
}

void undefined_op(vm *v, instruction *inst) {
    errorExit("exec undefined_op\n");
}

void nop_op(vm *v, instruction *inst) {
}