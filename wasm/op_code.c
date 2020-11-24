//
// Created by kingdo on 2020/11/25.
//
#include <include/wasm/op_code.h>

const char *opNames[256];

void init_opNames() {
    opNames[Unreachable] = "unreachable";
    opNames[Nop] = "nop";
    opNames[Block] = "block";
    opNames[Loop] = "loop";
    opNames[If] = "if";
    opNames[Else_] = "else";
    opNames[End_] = "end";
    opNames[Br] = "br";
    opNames[BrIf] = "br_if";
    opNames[BrTable] = "br_table";
    opNames[Return] = "return";
    opNames[Call] = "call";
    opNames[CallIndirect] = "call_indirect";
    opNames[Drop] = "drop";
    opNames[Select] = "select";
    opNames[LocalGet] = "local.get";
    opNames[LocalSet] = "local.set";
    opNames[LocalTee] = "local.tee";
    opNames[GlobalGet] = "global.get";
    opNames[GlobalSet] = "global.set";
    opNames[I32Load] = "i32.load";
    opNames[I64Load] = "i64.load";
    opNames[F32Load] = "f32.load";
    opNames[F64Load] = "f64.load";
    opNames[I32Load8S] = "i32.load8_s";
    opNames[I32Load8U] = "i32.load8_u";
    opNames[I32Load16S] = "i32.load16_s";
    opNames[I32Load16U] = "i32.load16_u";
    opNames[I64Load8S] = "i64.load8_s";
    opNames[I64Load8U] = "i64.load8_u";
    opNames[I64Load16S] = "i64.load16_s";
    opNames[I64Load16U] = "i64.load16_u";
    opNames[I64Load32S] = "i64.load32_s";
    opNames[I64Load32U] = "i64.load32_u";
    opNames[I32Store] = "i32.store";
    opNames[I64Store] = "i64.store";
    opNames[F32Store] = "f32.store";
    opNames[F64Store] = "f64.store";
    opNames[I32Store8] = "i32.store8";
    opNames[I32Store16] = "i32.store16";
    opNames[I64Store8] = "i64.store8";
    opNames[I64Store16] = "i64.store16";
    opNames[I64Store32] = "i64.store32";
    opNames[MemorySize] = "memory.size";
    opNames[MemoryGrow] = "memory.grow";
    opNames[I32Const] = "i32.const";
    opNames[I64Const] = "i64.const";
    opNames[F32Const] = "f32.const";
    opNames[F64Const] = "f64.const";
    opNames[I32Eqz] = "i32.eqz";
    opNames[I32Eq] = "i32.eq";
    opNames[I32Ne] = "i32.ne";
    opNames[I32LtS] = "i32.lt_s";
    opNames[I32LtU] = "i32.lt_u";
    opNames[I32GtS] = "i32.gt_s";
    opNames[I32GtU] = "i32.gt_u";
    opNames[I32LeS] = "i32.le_s";
    opNames[I32LeU] = "i32.le_u";
    opNames[I32GeS] = "i32.ge_s";
    opNames[I32GeU] = "i32.ge_u";
    opNames[I64Eqz] = "i64.eqz";
    opNames[I64Eq] = "i64.eq";
    opNames[I64Ne] = "i64.ne";
    opNames[I64LtS] = "i64.lt_s";
    opNames[I64LtU] = "i64.lt_u";
    opNames[I64GtS] = "i64.gt_s";
    opNames[I64GtU] = "i64.gt_u";
    opNames[I64LeS] = "i64.le_s";
    opNames[I64LeU] = "i64.le_u";
    opNames[I64GeS] = "i64.ge_s";
    opNames[I64GeU] = "i64.ge_u";
    opNames[F32Eq] = "f32.eq";
    opNames[F32Ne] = "f32.ne";
    opNames[F32Lt] = "f32.lt";
    opNames[F32Gt] = "f32.gt";
    opNames[F32Le] = "f32.le";
    opNames[F32Ge] = "f32.ge";
    opNames[F64Eq] = "f64.eq";
    opNames[F64Ne] = "f64.ne";
    opNames[F64Lt] = "f64.lt";
    opNames[F64Gt] = "f64.gt";
    opNames[F64Le] = "f64.le";
    opNames[F64Ge] = "f64.ge";
    opNames[I32Clz] = "i32.clz";
    opNames[I32Ctz] = "i32.ctz";
    opNames[I32PopCnt] = "i32.popcnt";
    opNames[I32Add] = "i32.add";
    opNames[I32Sub] = "i32.sub";
    opNames[I32Mul] = "i32.mul";
    opNames[I32DivS] = "i32.div_s";
    opNames[I32DivU] = "i32.div_u";
    opNames[I32RemS] = "i32.rem_s";
    opNames[I32RemU] = "i32.rem_u";
    opNames[I32And] = "i32.and";
    opNames[I32Or] = "i32.or";
    opNames[I32Xor] = "i32.xor";
    opNames[I32Shl] = "i32.shl";
    opNames[I32ShrS] = "i32.shr_s";
    opNames[I32ShrU] = "i32.shr_u";
    opNames[I32Rotl] = "i32.rotl";
    opNames[I32Rotr] = "i32.rotr";
    opNames[I64Clz] = "i64.clz";
    opNames[I64Ctz] = "i64.ctz";
    opNames[I64PopCnt] = "i64.popcnt";
    opNames[I64Add] = "i64.add";
    opNames[I64Sub] = "i64.sub";
    opNames[I64Mul] = "i64.mul";
    opNames[I64DivS] = "i64.div_s";
    opNames[I64DivU] = "i64.div_u";
    opNames[I64RemS] = "i64.rem_s";
    opNames[I64RemU] = "i64.rem_u";
    opNames[I64And] = "i64.and";
    opNames[I64Or] = "i64.or";
    opNames[I64Xor] = "i64.xor";
    opNames[I64Shl] = "i64.shl";
    opNames[I64ShrS] = "i64.shr_s";
    opNames[I64ShrU] = "i64.shr_u";
    opNames[I64Rotl] = "i64.rotl";
    opNames[I64Rotr] = "i64.rotr";
    opNames[F32Abs] = "f32.abs";
    opNames[F32Neg] = "f32.neg";
    opNames[F32Ceil] = "f32.ceil";
    opNames[F32Floor] = "f32.floor";
    opNames[F32Trunc] = "f32.trunc";
    opNames[F32Nearest] = "f32.nearest";
    opNames[F32Sqrt] = "f32.sqrt";
    opNames[F32Add] = "f32.add";
    opNames[F32Sub] = "f32.sub";
    opNames[F32Mul] = "f32.mul";
    opNames[F32Div] = "f32.div";
    opNames[F32Min] = "f32.min";
    opNames[F32Max] = "f32.max";
    opNames[F32CopySign] = "f32.copysign";
    opNames[F64Abs] = "f64.abs";
    opNames[F64Neg] = "f64.neg";
    opNames[F64Ceil] = "f64.ceil";
    opNames[F64Floor] = "f64.floor";
    opNames[F64Trunc] = "f64.trunc";
    opNames[F64Nearest] = "f64.nearest";
    opNames[F64Sqrt] = "f64.sqrt";
    opNames[F64Add] = "f64.add";
    opNames[F64Sub] = "f64.sub";
    opNames[F64Mul] = "f64.mul";
    opNames[F64Div] = "f64.div";
    opNames[F64Min] = "f64.min";
    opNames[F64Max] = "f64.max";
    opNames[F64CopySign] = "f64.copysign";
    opNames[I32WrapI64] = "i32.wrap_i64";
    opNames[I32TruncF32S] = "i32.trunc_f32_s";
    opNames[I32TruncF32U] = "i32.trunc_f32_u";
    opNames[I32TruncF64S] = "i32.trunc_f64_s";
    opNames[I32TruncF64U] = "i32.trunc_f64_u";
    opNames[I64ExtendI32S] = "i64.extend_i32_s";
    opNames[I64ExtendI32U] = "i64.extend_i32_u";
    opNames[I64TruncF32S] = "i64.trunc_f32_s";
    opNames[I64TruncF32U] = "i64.trunc_f32_u";
    opNames[I64TruncF64S] = "i64.trunc_f64_s";
    opNames[I64TruncF64U] = "i64.trunc_f64_u";
    opNames[F32ConvertI32S] = "f32.convert_i32_s";
    opNames[F32ConvertI32U] = "f32.convert_i32_u";
    opNames[F32ConvertI64S] = "f32.convert_i64_s";
    opNames[F32ConvertI64U] = "f32.convert_i64_u";
    opNames[F32DemoteF64] = "f32.demote_f64";
    opNames[F64ConvertI32S] = "f64.convert_i32_s";
    opNames[F64ConvertI32U] = "f64.convert_i32_u";
    opNames[F64ConvertI64S] = "f64.convert_i64_s";
    opNames[F64ConvertI64U] = "f64.convert_i64_u";
    opNames[F64PromoteF32] = "f64.promote_f32";
    opNames[I32ReinterpretF32] = "i32.reinterpret_f32";
    opNames[I64ReinterpretF64] = "i64.reinterpret_f64";
    opNames[F32ReinterpretI32] = "f32.reinterpret_i32";
    opNames[F64ReinterpretI64] = "f64.reinterpret_i64";
    opNames[I32Extend8S] = "i32.extend8_s";
    opNames[I32Extend16S] = "i32.extend16_s";
    opNames[I64Extend8S] = "i64.extend8_s";
    opNames[I64Extend16S] = "i64.extend16_s";
    opNames[I64Extend32S] = "i64.extend32_s";
    opNames[TruncSat] = "trunc_sat";
}
