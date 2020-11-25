//
// Created by kingdo on 2020/11/25.
//

#ifndef WCASM_OP_CODE_H
#define WCASM_OP_CODE_H

void init_opNames();

extern const char *opNames[256];

#define Unreachable        0x00 // unreachable

#define Nop                0x01 // nop

#define Block              0x02 // block rt in* end

#define Loop               0x03 // loop rt in* end

#define If                 0x04 // if rt in* else in* end

#define Else_              0x05 // else

#define End_               0x0B // end

#define Br                 0x0C // br l

#define BrIf               0x0D // br_if l

#define BrTable            0x0E // br_table l* lN

#define Return             0x0F // return

#define Call               0x10 // call x

#define CallIndirect       0x11 // call_indirect x

#define Drop               0x1A // drop

#define Select             0x1B // select

#define LocalGet           0x20 // local.get x

#define LocalSet           0x21 // local.set x

#define LocalTee           0x22 // local.tee x

#define GlobalGet          0x23 // global.get x

#define GlobalSet          0x24 // global.set x

#define I32Load            0x28 // i32.load m

#define I64Load            0x29 // i64.load m

#define F32Load            0x2A // f32.load m

#define F64Load            0x2B // f64.load m

#define I32Load8S          0x2C // i32.load8_s m

#define I32Load8U          0x2D // i32.load8_u m

#define I32Load16S         0x2E // i32.load16_s m

#define I32Load16U         0x2F // i32.load16_u m

#define I64Load8S          0x30 // i64.load8_s m

#define I64Load8U          0x31 // i64.load8_u m

#define I64Load16S         0x32 // i64.load16_s m

#define I64Load16U         0x33 // i64.load16_u m

#define I64Load32S         0x34 // i64.load32_s m

#define I64Load32U         0x35 // i64.load32_u m

#define I32Store           0x36 // i32.store m

#define I64Store           0x37 // i64.store m

#define F32Store           0x38 // f32.store m

#define F64Store           0x39 // f64.store m

#define I32Store8          0x3A // i32.store8 m

#define I32Store16         0x3B // i32.store16 m

#define I64Store8          0x3C // i64.store8 m

#define I64Store16         0x3D // i64.store16 m

#define I64Store32         0x3E // i64.store32 m

#define MemorySize         0x3F // memory.size

#define MemoryGrow         0x40 // memory.grow

#define I32Const           0x41 // i32.const n

#define I64Const           0x42 // i64.const n

#define F32Const           0x43 // f32.const z

#define F64Const           0x44 // f64.const z

#define I32Eqz             0x45 // i32.eqz

#define I32Eq              0x46 // i32.eq

#define I32Ne              0x47 // i32.ne

#define I32LtS             0x48 // i32.lt_s

#define I32LtU             0x49 // i32.lt_u

#define I32GtS             0x4A // i32.gt_s

#define I32GtU             0x4B // i32.gt_u

#define I32LeS             0x4C // i32.le_s

#define I32LeU             0x4D // i32.le_u

#define I32GeS             0x4E // i32.ge_s

#define I32GeU             0x4F // i32.ge_u

#define I64Eqz             0x50 // i64.eqz

#define I64Eq              0x51 // i64.eq

#define I64Ne              0x52 // i64.ne

#define I64LtS             0x53 // i64.lt_s

#define I64LtU             0x54 // i64.lt_u

#define I64GtS             0x55 // i64.gt_s

#define I64GtU             0x56 // i64.gt_u

#define I64LeS             0x57 // i64.le_s

#define I64LeU             0x58 // i64.le_u

#define I64GeS             0x59 // i64.ge_s

#define I64GeU             0x5A // i64.ge_u

#define F32Eq              0x5B // f32.eq

#define F32Ne              0x5C // f32.ne

#define F32Lt              0x5D // f32.lt

#define F32Gt              0x5E // f32.gt

#define F32Le              0x5F // f32.le

#define F32Ge              0x60 // f32.ge

#define F64Eq              0x61 // f64.eq

#define F64Ne              0x62 // f64.ne

#define F64Lt              0x63 // f64.lt

#define F64Gt              0x64 // f64.gt

#define F64Le              0x65 // f64.le

#define F64Ge              0x66 // f64.ge

#define I32Clz             0x67 // i32.clz

#define I32Ctz             0x68 // i32.ctz

#define I32PopCnt          0x69 // i32.popcnt

#define I32Add             0x6A // i32.add

#define I32Sub             0x6B // i32.sub

#define I32Mul             0x6C // i32.mul

#define I32DivS            0x6D // i32.div_s

#define I32DivU            0x6E // i32.div_u

#define I32RemS            0x6F // i32.rem_s

#define I32RemU            0x70 // i32.rem_u

#define I32And             0x71 // i32.and

#define I32Or              0x72 // i32.or

#define I32Xor             0x73 // i32.xor

#define I32Shl             0x74 // i32.shl

#define I32ShrS            0x75 // i32.shr_s

#define I32ShrU            0x76 // i32.shr_u

#define I32Rotl            0x77 // i32.rotl

#define I32Rotr            0x78 // i32.rotr

#define I64Clz             0x79 // i64.clz

#define I64Ctz             0x7A // i64.ctz

#define I64PopCnt          0x7B // i64.popcnt

#define I64Add             0x7C // i64.add

#define I64Sub             0x7D // i64.sub

#define I64Mul             0x7E // i64.mul

#define I64DivS            0x7F // i64.div_s

#define I64DivU            0x80 // i64.div_u

#define I64RemS            0x81 // i64.rem_s

#define I64RemU            0x82 // i64.rem_u

#define I64And             0x83 // i64.and

#define I64Or              0x84 // i64.or

#define I64Xor             0x85 // i64.xor

#define I64Shl             0x86 // i64.shl

#define I64ShrS            0x87 // i64.shr_s

#define I64ShrU            0x88 // i64.shr_u

#define I64Rotl            0x89 // i64.rotl

#define I64Rotr            0x8A // i64.rotr

#define F32Abs             0x8B // f32.abs

#define F32Neg             0x8C // f32.neg

#define F32Ceil            0x8D // f32.ceil

#define F32Floor           0x8E // f32.floor

#define F32Trunc           0x8F // f32.trunc

#define F32Nearest         0x90 // f32.nearest

#define F32Sqrt            0x91 // f32.sqrt

#define F32Add             0x92 // f32.add

#define F32Sub             0x93 // f32.sub

#define F32Mul             0x94 // f32.mul

#define F32Div             0x95 // f32.div

#define F32Min             0x96 // f32.min

#define F32Max             0x97 // f32.max

#define F32CopySign        0x98 // f32.copysign

#define F64Abs             0x99 // f64.abs

#define F64Neg             0x9A // f64.neg

#define F64Ceil            0x9B // f64.ceil

#define F64Floor           0x9C // f64.floor

#define F64Trunc           0x9D // f64.trunc

#define F64Nearest         0x9E // f64.nearest

#define F64Sqrt            0x9F // f64.sqrt

#define F64Add             0xA0 // f64.add

#define F64Sub             0xA1 // f64.sub

#define F64Mul             0xA2 // f64.mul

#define F64Div             0xA3 // f64.div

#define F64Min             0xA4 // f64.min

#define F64Max             0xA5 // f64.max

#define F64CopySign        0xA6 // f64.copysign

#define I32WrapI64         0xA7 // i32.wrap_i64

#define I32TruncF32S       0xA8 // i32.trunc_f32_s

#define I32TruncF32U       0xA9 // i32.trunc_f32_u

#define I32TruncF64S       0xAA // i32.trunc_f64_s

#define I32TruncF64U       0xAB // i32.trunc_f64_u

#define I64ExtendI32S      0xAC // i64.extend_i32_s

#define I64ExtendI32U      0xAD // i64.extend_i32_u

#define I64TruncF32S       0xAE // i64.trunc_f32_s

#define I64TruncF32U       0xAF // i64.trunc_f32_u

#define I64TruncF64S       0xB0 // i64.trunc_f64_s

#define I64TruncF64U       0xB1 // i64.trunc_f64_u

#define F32ConvertI32S     0xB2 // f32.convert_i32_s

#define F32ConvertI32U     0xB3 // f32.convert_i32_u

#define F32ConvertI64S     0xB4 // f32.convert_i64_s

#define F32ConvertI64U     0xB5 // f32.convert_i64_u

#define F32DemoteF64       0xB6 // f32.demote_f64

#define F64ConvertI32S     0xB7 // f64.convert_i32_s

#define F64ConvertI32U     0xB8 // f64.convert_i32_u

#define F64ConvertI64S     0xB9 // f64.convert_i64_s

#define F64ConvertI64U     0xBA // f64.convert_i64_u

#define F64PromoteF32      0xBB // f64.promote_f32

#define I32ReinterpretF32  0xBC // i32.reinterpret_f32

#define I64ReinterpretF64  0xBD // i64.reinterpret_f64

#define F32ReinterpretI32  0xBE // f32.reinterpret_i32

#define F64ReinterpretI64  0xBF // f64.reinterpret_i64

#define I32Extend8S        0xC0 // i32.extend8_s

#define I32Extend16S       0xC1 // i32.extend16_s

#define I64Extend8S        0xC2 // i64.extend8_s

#define I64Extend16S       0xC3 // i64.extend16_s

#define I64Extend32S       0xC4 // i64.extend32_s

#define TruncSat           0xFC // <i32|64>.trunc_sat_<f32|64>_<s|u>


#endif //WCASM_OP_CODE_H
