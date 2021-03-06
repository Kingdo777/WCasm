//
// Created by kingdo on 2020/11/26.
//
#include <string.h>
#include <include/tool/error/error_handle.h>
#include "include/wasm/op_code.h"
#include "include/wasm/vm/vm.h"
#include "include/debug.h"

void (*op[256])(vm *v, instruction *inst);

vm *createVM() {
    vm *v = malloc(sizeof(vm));
    memset(v, 0, sizeof(vm));
    initStack(&v->operandStack);
    initControlStack(&v->controlStack);
    return v;
}

void destroyVM(vm *v) {
    if (NULL != v) {
        freeStack(&v->operandStack);
        freeControlStack(&v->controlStack);
        free(v);
    }
}

void execInst(vm *v, instruction *inst) {
    op[inst->op_code](v, inst);
}

void print_instruction(instruction *inst, int format_blank_count);

function *getMainFunc(vm *v) {
    function_index f_index = -1;
    module *m = v->m;
    if (m->start_sec.start_segment_count == 1) {
        /*获取启动段的启动函数的索引*/
        f_index = *(m->start_sec.start_segment_addr);
    } else {
        for (int i = 0; i < m->export_sec.export_segment_count; ++i) {
            export_pointer ep = m->export_sec.export_segment_addr + i;
            if (ep->ex_desc.tag == func_im_export_tag && !strcmp((const char *) ep->name, "main")) {
                f_index = ep->ex_desc.index;
                break;
            }
        }
    }
    function *f = NULL;
    if (f_index != -1)
        f = v->func.get_ele(&v->func, f_index);
    return f;
}

void loop(vm *v) {
    function *f = getMainFunc(v);
    if (NULL == f) {
        printf("have no Main Function\n");
    } else {
        /*启动函数一定是内部函数，减去导入段的函数个数，就是内部函数的索引*/
        callInternalFunc(v, f);
        while (get_control_stack_size(&v->controlStack) != 0) {
            control_frame *cf = get_top_control_stack_ele_p(&v->controlStack);
            if (cf->pc == cf->instructions->size) {
                exitBlock(v);
            } else {
                instruction *inst = cf->instructions->get_ele(cf->instructions, cf->pc++);
#ifdef EXEC_DEBUG
                print_instruction(inst, 0);
#endif
                execInst(v, inst);
            }
        }
    }
}

void exec(vm *v, module *m) {
    v->m = m;
    initMemory(v);
    initGlobalVar(v);
    initFunction(v);
    initTable(v);
    puts("\n######################### RUN ########################\n");
    loop(v);
    puts("\n####################### SUCCESS ######################\n");
    freeTable(v);
    freeFunction(v);
    freeGlobalVar(v);
    freeMemory(v);
    v->m = NULL;
}

void init_op() {
    for (int i = 0; i < 256; ++i) {
        op[i] = undefined_op;
    }
    op[Unreachable] = unreachable_op;
    op[Nop] = nop_op;
    op[Block] = block_op;
    op[Loop] = loop_op;
    op[If] = if_op;
    /*下面两个其实是伪指令*/
    op[Else_] = else_op;
    op[End_] = end_op;
    op[Br] = br_op;
    op[BrIf] = brIf_op;
    op[BrTable] = brTable_op;
    op[Return] = return_op;
    op[Call] = call_op;
    op[CallIndirect] = callIndirect_op;
    op[Drop] = drop_op;
    op[Select] = select_op;
    op[LocalGet] = localGet_op;
    op[LocalSet] = localSet_op;
    op[LocalTee] = localTee_op;
    op[GlobalGet] = globalGet_op;
    op[GlobalSet] = globalSet_op;
    op[I32Load] = i32Load_op;
    op[I64Load] = i64Load_op;
    op[F32Load] = f32Load_op;
    op[F64Load] = f64Load_op;
    op[I32Load8S] = i32Load8S_op;
    op[I32Load8U] = i32Load8U_op;
    op[I32Load16S] = i32Load16S_op;
    op[I32Load16U] = i32Load16U_op;
    op[I64Load8S] = i64Load8S_op;
    op[I64Load8U] = i64Load8U_op;
    op[I64Load16S] = i64Load16S_op;
    op[I64Load16U] = i64Load16U_op;
    op[I64Load32S] = i64Load32S_op;
    op[I64Load32U] = i64Load32U_op;
    op[I32Store] = i32Store_op;
    op[I64Store] = i64Store_op;
    op[F32Store] = f32Store_op;
    op[F64Store] = f64Store_op;
    op[I32Store8] = i32Store8_op;
    op[I32Store16] = i32Store16_op;
    op[I64Store8] = i64Store8_op;
    op[I64Store16] = i64Store16_op;
    op[I64Store32] = i64Store32_op;
    op[MemorySize] = memorySize_op;
    op[MemoryGrow] = memoryGrow_op;
    op[I32Const] = i32Const_op;
    op[I64Const] = i64Const_op;
    op[F32Const] = f32Const_op;
    op[F64Const] = f64Const_op;
    op[I32Eqz] = i32Eqz_op;
    op[I32Eq] = i32Eq_op;
    op[I32Ne] = i32Ne_op;
    op[I32LtS] = i32Lts_op;
    op[I32LtU] = i32Ltu_op;
    op[I32GtS] = i32Gts_op;
    op[I32GtU] = i32Gtu_op;
    op[I32LeS] = i32Les_op;
    op[I32LeU] = i32Leu_op;
    op[I32GeS] = i32Ges_op;
    op[I32GeU] = i32Geu_op;
    op[I64Eqz] = i64Eqz_op;
    op[I64Eq] = i64Eq_op;
    op[I64Ne] = i64Ne_op;
    op[I64LtS] = i64Lts_op;
    op[I64LtU] = i64Ltu_op;
    op[I64GtS] = i64Gts_op;
    op[I64GtU] = i64Gtu_op;
    op[I64LeS] = i64Les_op;
    op[I64LeU] = i64Leu_op;
    op[I64GeS] = i64Ges_op;
    op[I64GeU] = i64Geu_op;
    op[F32Eq] = f32Eq_op;
    op[F32Ne] = f32Ne_op;
    op[F32Lt] = f32Lt_op;
    op[F32Gt] = f32Gt_op;
    op[F32Le] = f32Le_op;
    op[F32Ge] = f32Ge_op;
    op[F64Eq] = f64Eq_op;
    op[F64Ne] = f64Ne_op;
    op[F64Lt] = f64Lt_op;
    op[F64Gt] = f64Gt_op;
    op[F64Le] = f64Le_op;
    op[F64Ge] = f64Ge_op;
    op[I32Clz] = i32Clz_op;
    op[I32Ctz] = i32Ctz_op;
    op[I32PopCnt] = i32Popcnt_op;
    op[I32Add] = i32Add_op;
    op[I32Sub] = i32Sub_op;
    op[I32Mul] = i32Mul_op;
    op[I32DivS] = i32DivS_op;
    op[I32DivU] = i32DivU_op;
    op[I32RemS] = i32RemS_op;
    op[I32RemU] = i32RemU_op;
    op[I32And] = i32And_op;
    op[I32Or] = i32Or_op;
    op[I32Xor] = i32Xor_op;
    op[I32Shl] = i32Shl_op;
    op[I32ShrS] = i32ShrS_op;
    op[I32ShrU] = i32ShrU_op;
    op[I32Rotl] = i32RotL_op;
    op[I32Rotr] = i32RotR_op;
    op[I64Clz] = i64Clz_op;
    op[I64Ctz] = i64Ctz_op;
    op[I64PopCnt] = i64Popcnt_op;
    op[I64Add] = i64Add_op;
    op[I64Sub] = i64Sub_op;
    op[I64Mul] = i64Mul_op;
    op[I64DivS] = i64DivS_op;
    op[I64DivU] = i64DivU_op;
    op[I64RemS] = i64RemS_op;
    op[I64RemU] = i64RemU_op;
    op[I64And] = i64And_op;
    op[I64Or] = i64Or_op;
    op[I64Xor] = i64Xor_op;
    op[I64Shl] = i64Shl_op;
    op[I64ShrS] = i64ShrS_op;
    op[I64ShrU] = i64ShrU_op;
    op[I64Rotl] = i64RotL_op;
    op[I64Rotr] = i64RotR_op;
    op[F32Abs] = f32Abs_op;
    op[F32Neg] = f32Neg_op;
    op[F32Ceil] = f32Ceil_op;
    op[F32Floor] = f32Floor_op;
    op[F32Trunc] = f32Trunc_op;
    op[F32Nearest] = f32Nearest_op;
    op[F32Sqrt] = f32Sqrt_op;
    op[F32Add] = f32Add_op;
    op[F32Sub] = f32Sub_op;
    op[F32Mul] = f32mul_op;
    op[F32Div] = f32Div_op;
    op[F32Min] = f32min_op;
    op[F32Max] = f32Max_op;
    op[F32CopySign] = f32Copysign_op;
    op[F64Abs] = f64Abs_op;
    op[F64Neg] = f64Neg_op;
    op[F64Ceil] = f64Ceil_op;
    op[F64Floor] = f64Floor_op;
    op[F64Trunc] = f64Trunc_op;
    op[F64Nearest] = f64Nearest_op;
    op[F64Sqrt] = f64Sqrt_op;
    op[F64Add] = f64Add_op;
    op[F64Sub] = f64Sub_op;
    op[F64Mul] = f64mul_op;
    op[F64Div] = f64Div_op;
    op[F64Min] = f64min_op;
    op[F64Max] = f64Max_op;
    op[F64CopySign] = f64Copysign_op;
    op[I32WrapI64] = i32wrapI64_op;
    op[I32TruncF32S] = i32TruncF32S_op;
    op[I32TruncF32U] = i32TruncF32U_op;
    op[I32TruncF64S] = i32TruncF64S_op;
    op[I32TruncF64U] = i32TruncF64U_op;
    op[I64ExtendI32S] = i64ExtendI32S_op;
    op[I64ExtendI32U] = i64ExtendI32U_op;
    op[I64TruncF32S] = i64TruncF32S_op;
    op[I64TruncF32U] = i64TruncF32U_op;
    op[I64TruncF64S] = i64TruncF64S_op;
    op[I64TruncF64U] = i64TruncF64U_op;
    op[F32ConvertI32S] = f32ConvertI32S_op;
    op[F32ConvertI32U] = f32ConvertI32U_op;
    op[F32ConvertI64S] = f32ConvertI64S_op;
    op[F32ConvertI64U] = f32ConvertI64U_op;
    op[F32DemoteF64] = f32DemoteF64_op;
    op[F64ConvertI32S] = f64ConvertI32S_op;
    op[F64ConvertI32U] = f64ConvertI32U_op;
    op[F64ConvertI64S] = f64ConvertI64S_op;
    op[F64ConvertI64U] = f64ConvertI64U_op;
    op[F64PromoteF32] = f64PromoteF32_op;
    op[I32ReinterpretF32] = i32ReinterpretF32_op;
    op[I64ReinterpretF64] = i64ReinterpretF64_op;
    op[F32ReinterpretI32] = f32ReinterpretI32_op;
    op[F64ReinterpretI64] = f64ReinterpretI64_op;
    op[I32Extend8S] = i32Extend8S_op;
    op[I32Extend16S] = i32Extend16S_op;
    op[I64Extend8S] = i64Extend8S_op;
    op[I64Extend16S] = i64Extend16S_op;
    op[I64Extend32S] = i64Extend32S_op;
    op[TruncSat] = truncSat_op;
}