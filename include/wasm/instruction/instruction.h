//
// Created by kingdo on 2020/11/25.
//

#ifndef WCASM_INSTRUCTION_H
#define WCASM_INSTRUCTION_H

#include "include/tool/type.h"
#include "include/tool/vector/vector.h"
#include "include/wasm/op_code.h"

#define getOpName(ins) opNames[ins->op_code]


typedef struct {
    byte op_code;
    void *arg;
} instruction;

typedef struct {
    /*内存立即数*/
    uint32 align;
    /*目前内存支持的大小其实只有4G,因此uint32其实已经足够*/
    uint64 offset;
} memArgs;

typedef struct {
    blocktype blockType;
    vec instructions;
} blockArgs;

typedef struct {
    blocktype blockType;
    vec instructions1;
    vec instructions2;
} ifArgs;


typedef struct {
    labelIndex defaultLabels;
    uint32 labelCount;
    labelIndex *labels;
} brTableArgs;

typedef function_index callArgs;

typedef struct {
    type_index t_index;
    table_index tableIndex;
} call_indirectArgs;

typedef byte truncSatArgs;

#endif //WCASM_INSTRUCTION_H
