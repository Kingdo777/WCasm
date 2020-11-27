//
// Created by kingdo on 2020/11/26.
//

#ifndef WCASM_VM_H
#define WCASM_VM_H

#include "include/wasm/module.h"
#include "include/tool/stack/stack.h"

typedef struct {
    uint32 cs;
    uint64 ip;
} PC;

typedef struct {
    stack operandStack;
    memory memory;
    PC pc;
} vm;

vm *createVM();

void destroyVM(vm *v);

void execCode(vm *v, module *m);

void init_op();

/*参数指令执行*/
void drop_op(vm *v, instruction *inst);

void select_op(vm *v, instruction *inst);

/*数值指令*/
/*常量数值指令*/
void i32Const_op(vm *v, instruction *inst);

void i64Const_op(vm *v, instruction *inst);

void f32Const_op(vm *v, instruction *inst);

void f64Const_op(vm *v, instruction *inst);

/*测试数值指令*/
void i32Eqz_op(vm *v, instruction *inst);

void i64Eqz_op(vm *v, instruction *inst);

/*比较数值指令*/
void i32Eq_op(vm *v, instruction *inst);

void i32Ne_op(vm *v, instruction *inst);

void i32Lts_op(vm *v, instruction *inst);

void i32Ltu_op(vm *v, instruction *inst);

void i32Gts_op(vm *v, instruction *inst);

void i32Gtu_op(vm *v, instruction *inst);

void i32Les_op(vm *v, instruction *inst);

void i32Leu_op(vm *v, instruction *inst);

void i32Ges_op(vm *v, instruction *inst);

void i32Geu_op(vm *v, instruction *inst);

void i64Eq_op(vm *v, instruction *inst);

void i64Ne_op(vm *v, instruction *inst);

void i64Lts_op(vm *v, instruction *inst);

void i64Ltu_op(vm *v, instruction *inst);

void i64Gts_op(vm *v, instruction *inst);

void i64Gtu_op(vm *v, instruction *inst);

void i64Les_op(vm *v, instruction *inst);

void i64Leu_op(vm *v, instruction *inst);

void i64Ges_op(vm *v, instruction *inst);

void i64Geu_op(vm *v, instruction *inst);

void f32Eq_op(vm *v, instruction *inst);

void f32Ne_op(vm *v, instruction *inst);

void f32Lt_op(vm *v, instruction *inst);

void f32Gt_op(vm *v, instruction *inst);

void f32Le_op(vm *v, instruction *inst);

void f32Ge_op(vm *v, instruction *inst);

void f64Eq_op(vm *v, instruction *inst);

void f64Ne_op(vm *v, instruction *inst);

void f64Lt_op(vm *v, instruction *inst);

void f64Gt_op(vm *v, instruction *inst);

void f64Le_op(vm *v, instruction *inst);

void f64Ge_op(vm *v, instruction *inst);

/*一元数值指令*/
void i32Clz_op(vm *v, instruction *inst);

void i32Ctz_op(vm *v, instruction *inst);

void i32Popcnt_op(vm *v, instruction *inst);

void i64Clz_op(vm *v, instruction *inst);

void i64Ctz_op(vm *v, instruction *inst);

void i64Popcnt_op(vm *v, instruction *inst);

void f32Abs_op(vm *v, instruction *inst);

void f32Neg_op(vm *v, instruction *inst);

void f32Ceil_op(vm *v, instruction *inst);

void f32Floor_op(vm *v, instruction *inst);

void f32Trunc_op(vm *v, instruction *inst);

void f32Nearest_op(vm *v, instruction *inst);

void f32Sqrt_op(vm *v, instruction *inst);

void f64Abs_op(vm *v, instruction *inst);

void f64Neg_op(vm *v, instruction *inst);

void f64Ceil_op(vm *v, instruction *inst);

void f64Floor_op(vm *v, instruction *inst);

void f64Trunc_op(vm *v, instruction *inst);

void f64Nearest_op(vm *v, instruction *inst);

void f64Sqrt_op(vm *v, instruction *inst);

/*二元数值指令*/
void i32Add_op(vm *v, instruction *inst);

void i32Sub_op(vm *v, instruction *inst);

void i32Mul_op(vm *v, instruction *inst);

void i32DivS_op(vm *v, instruction *inst);

void i32DivU_op(vm *v, instruction *inst);

void i32RemS_op(vm *v, instruction *inst);

void i32RemU_op(vm *v, instruction *inst);

void i32And_op(vm *v, instruction *inst);

void i32Or_op(vm *v, instruction *inst);

void i32Xor_op(vm *v, instruction *inst);

void i32Shl_op(vm *v, instruction *inst);

void i32ShrS_op(vm *v, instruction *inst);

void i32ShrU_op(vm *v, instruction *inst);

void i32RotL_op(vm *v, instruction *inst);

void i32RotR_op(vm *v, instruction *inst);

void i64Add_op(vm *v, instruction *inst);

void i64Sub_op(vm *v, instruction *inst);

void i64Mul_op(vm *v, instruction *inst);

void i64DivS_op(vm *v, instruction *inst);

void i64DivU_op(vm *v, instruction *inst);

void i64RemS_op(vm *v, instruction *inst);

void i64RemU_op(vm *v, instruction *inst);

void i64And_op(vm *v, instruction *inst);

void i64Or_op(vm *v, instruction *inst);

void i64Xor_op(vm *v, instruction *inst);

void i64Shl_op(vm *v, instruction *inst);

void i64ShrS_op(vm *v, instruction *inst);

void i64ShrU_op(vm *v, instruction *inst);

void i64RotL_op(vm *v, instruction *inst);

void i64RotR_op(vm *v, instruction *inst);

void f32Add_op(vm *v, instruction *inst);

void f32Sub_op(vm *v, instruction *inst);

void f32mul_op(vm *v, instruction *inst);

void f32Div_op(vm *v, instruction *inst);

void f32min_op(vm *v, instruction *inst);

void f32Max_op(vm *v, instruction *inst);

void f32Copysign_op(vm *v, instruction *inst);

void f64Add_op(vm *v, instruction *inst);

void f64Sub_op(vm *v, instruction *inst);

void f64mul_op(vm *v, instruction *inst);

void f64Div_op(vm *v, instruction *inst);

void f64min_op(vm *v, instruction *inst);

void f64Max_op(vm *v, instruction *inst);

void f64Copysign_op(vm *v, instruction *inst);

/*类型转化值指令*/
void i32wrapI64_op(vm *v, instruction *inst);

void i64ExtendI32S_op(vm *v, instruction *inst);

void i64ExtendI32U_op(vm *v, instruction *inst);

void f32ConvertI32S_op(vm *v, instruction *inst);

void f32ConvertI32U_op(vm *v, instruction *inst);

void f32ConvertI64S_op(vm *v, instruction *inst);

void f32ConvertI64U_op(vm *v, instruction *inst);

void f32DemoteF64_op(vm *v, instruction *inst);

void f64ConvertI32S_op(vm *v, instruction *inst);

void f64ConvertI32U_op(vm *v, instruction *inst);

void f64ConvertI64S_op(vm *v, instruction *inst);

void f64ConvertI64U_op(vm *v, instruction *inst);

void f64PromoteF32_op(vm *v, instruction *inst);

void i32Extend8S_op(vm *v, instruction *inst);

void i32Extend16S_op(vm *v, instruction *inst);

void i64Extend8S_op(vm *v, instruction *inst);

void i64Extend16S_op(vm *v, instruction *inst);

void i64Extend32S_op(vm *v, instruction *inst);

void i32ReinterpretF32_op(vm *v, instruction *inst);

void i64ReinterpretF64_op(vm *v, instruction *inst);

void f32ReinterpretI32_op(vm *v, instruction *inst);

void f64ReinterpretI64_op(vm *v, instruction *inst);

void i32TruncF32S_op(vm *v, instruction *inst);

void i32TruncF32U_op(vm *v, instruction *inst);

void i32TruncF64S_op(vm *v, instruction *inst);

void i32TruncF64U_op(vm *v, instruction *inst);

void i64TruncF32S_op(vm *v, instruction *inst);

void i64TruncF32U_op(vm *v, instruction *inst);

void i64TruncF64S_op(vm *v, instruction *inst);

void i64TruncF64U_op(vm *v, instruction *inst);

void truncSat_op(vm *v, instruction *inst);

/*内存指令*/
void init_memory(module *module, memory *memory);

void freeMemory(memory *memory);

uint32 get_memoryCount(memory *memory);

#endif //WCASM_VM_H
