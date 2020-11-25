//
// Created by kingdo on 2020/11/25.
//

#include <include/wasm/wasm_reader/wasm_reader.h>
#include <include/wasm/op_code.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/wasm/instruction/instruction.h"

instruction read_instruction(wasm_reader *wr);

void *read_arg(wasm_reader *wr, byte op_code);

void is_end(byte op) {
    if (op != End_) {
        fprintf(stderr, "the op must is END!\n");
        exit(0);
    }
}

void *read_arg(wasm_reader *wr, byte op_code) {
    void *arg = NULL;
    vec *v = NULL;
    switch (op_code) {
        case Block:
        case Loop:
            arg = (blockArgs *) malloc(sizeof(blockArgs));
            ((blockArgs *) arg)->blockType = wr->wr_op.read_int32_from_leb128(wr);
            wr->wr_op.read_instructions(wr, &((blockArgs *) arg)->instructions);
            v = &((blockArgs *) arg)->instructions;
            is_end(((instruction *) v->get_last_ele(v))->op_code);
            break;
        case If:
            arg = (ifArgs *) malloc(sizeof(ifArgs));
            ((ifArgs *) arg)->blockType = wr->wr_op.read_int32_from_leb128(wr);
            wr->wr_op.read_instructions(wr, &((ifArgs *) arg)->instructions1);
            v = &((ifArgs *) arg)->instructions1;
            byte op = ((instruction *) v->get_last_ele(v))->op_code;
            if (op == Else_) {
                wr->wr_op.read_instructions(wr, &((ifArgs *) arg)->instructions2);
                v = &((ifArgs *) arg)->instructions2;
                op = ((instruction *) v->get_last_ele(v))->op_code;
            }
            is_end(op);
            break;
        case Br:
        case BrIf:
            arg = (brArgs *) malloc(sizeof(brArgs));
            *(brArgs *) arg = wr->wr_op.read_uint32_from_leb128(wr);
            break;
        case BrTable:
            arg = (brTableArgs *) malloc(sizeof(brTableArgs));
            ((brTableArgs *) arg)->labelCount = wr->wr_op.read_uint32_from_leb128(wr);
            ((brTableArgs *) arg)->labels = malloc(sizeof(labelIndex) * ((brTableArgs *) arg)->labelCount);
            for (int i = 0; i < ((brTableArgs *) arg)->labelCount; ++i) {
                *(((brTableArgs *) arg)->labels + i) = wr->wr_op.read_uint32_from_leb128(wr);
            }
            ((brTableArgs *) arg)->defaultLabels = wr->wr_op.read_uint32_from_leb128(wr);
            break;
        case Call:
            arg = (callArgs *) malloc(sizeof(callArgs));
            *((callArgs *) arg) = wr->wr_op.read_uint32_from_leb128(wr);
            break;
        case CallIndirect:
            arg = (call_indirectArgs *) malloc(sizeof(call_indirectArgs));
            ((call_indirectArgs *) arg)->index = wr->wr_op.read_uint32_from_leb128(wr);
            ((call_indirectArgs *) arg)->tableIndex = 0;
            if (0 != wr->wr_op.read_uint32_from_leb128(wr)) {
                fprintf(stderr, "table index can only be 0\n");
                exit(0);
            }
            break;
        case LocalGet:
        case LocalSet:
        case LocalTee:
        case GlobalGet:
        case GlobalSet:
            arg = (uint32 *) malloc(sizeof(uint32 *));
            *(uint32 *) arg = wr->wr_op.read_uint32_from_leb128(wr);
            break;
        case MemorySize:
        case MemoryGrow:
            arg = (mem_index *) malloc(sizeof(mem_index));
            *(mem_index *) arg = 0;
            if (0 != wr->wr_op.read_uint32_from_leb128(wr)) {
                fprintf(stderr, "mem index can only be 0\n");
                exit(0);
            }
            break;
        case I32Const:
            arg = (int32 *) malloc(sizeof(int32));
            *(int32 *) arg = wr->wr_op.read_int32_from_leb128(wr);
            break;
        case I64Const:
            arg = (int64 *) malloc(sizeof(int64));
            *(int64 *) arg = wr->wr_op.read_int64_from_leb128(wr);
            break;
        case F32Const:
            arg = (float32 *) malloc(sizeof(float32));
            *(float32 *) arg = wr->wr_op.read_float32(wr);
            break;
        case F64Const:
            arg = (float64 *) malloc(sizeof(float64));
            *(float64 *) arg = wr->wr_op.read_float64(wr);
            break;
        case TruncSat:
            arg = (truncSatArgs *) malloc(sizeof(truncSatArgs));
            *((truncSatArgs *) arg) = wr->wr_op.read_byte(wr);
            break;
        default:
            if (I32Load <= op_code && op_code <= I64Store32) {
                arg = (memArgs *) (malloc(sizeof(memArgs)));
                ((memArgs *) arg)->align = wr->wr_op.read_uint32_from_leb128(wr);
                ((memArgs *) arg)->offset = wr->wr_op.read_uint32_from_leb128(wr);
                break;
            }
    }
    return arg;
}

void read_instructions(wasm_reader *wr, vec *instructions) {
    size_t a;
    init_vec(instructions, sizeof(instruction));
    instruction inst;
    do {
        inst = wr->wr_op.read_instruction(wr);
        instructions->append(instructions, &inst);
    } while (inst.op_code != End_ && inst.op_code != Else_);
}

instruction read_instruction(wasm_reader *wr) {
    instruction inst;
    inst.op_code = wr->wr_op.read_byte(wr);
    inst.arg = read_arg(wr, inst.op_code);
    return inst;
}