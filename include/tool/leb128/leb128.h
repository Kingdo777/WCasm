//
// Created by kingdo on 2020/11/20.
//

#ifndef WCASM_LEB128_H
#define WCASM_LEB128_H


#include <include/tool/type.h>

typedef struct {
    int len;
    uint64 value;
} leb128_uint64_t;

typedef struct {
    int len;
    int64 value;
} leb128_int64_t;

typedef struct {
    int len;
    uint32 value;
} leb128_uint32_t;

typedef struct {
    int len;
    int32 value;
} leb128_int32_t;

leb128_uint64_t leb128_to_uint64(byte leb[]);

leb128_uint32_t leb128_to_uint32(byte leb[]);

leb128_int64_t leb128_to_int64(byte leb[]);

leb128_int32_t leb128_to_int32(byte leb[]);

#endif //WCASM_LEB128_H
