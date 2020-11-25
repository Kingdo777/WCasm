//
// Created by kingdo on 2020/11/25.
//

#ifndef WCASM_INSTRUCTION_H
#define WCASM_INSTRUCTION_H

#include <include/tool/type.h>
#include <include/tool/vector/vector.h>

#define getOpName(ins) opNames[ins.op_code]

typedef int blocktype;
typedef uint32 labelIndex;

typedef struct {
    byte op_code;
    void *arg;
} instruction;

typedef struct {
    /*内存立即数*/
    uint32 align;
    uint32 offset;
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

typedef labelIndex brArgs, brIfArgs;

typedef struct {
    labelIndex defaultLabels;
    uint32 labelCount;
    labelIndex *labels;
} brTableArgs;

typedef func_index callArgs;

typedef struct {
    type_index index;
    table_index tableIndex;
} call_indirectArgs;

typedef byte truncSatArgs;

#endif //WCASM_INSTRUCTION_H
