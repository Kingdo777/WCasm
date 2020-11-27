//
// Created by kingdo on 2020/11/21.
//

#ifndef WCASM_WASM_READER_H
#define WCASM_WASM_READER_H

#include <stdlib.h>
#include "include/tool/type.h"
#include "include/wasm/instruction/instruction.h"
#include "include/wasm/module.h"
#include "include/tool/leb128/leb128.h"


typedef struct wasm_reader {
    byte *wasm_model_addr;  /*mmap的内存地址*/
    uint64 index;           /*内存索引,记录当前解析的位置*/
    int wasm_model_fd;      /*二进制文件句柄*/
    size_t model_size;

    struct {
        void (*open)(struct wasm_reader *, const char *filename);

        byte (*read_byte)(struct wasm_reader *);

        void (*read_N_byte)(struct wasm_reader *wr, byte *buffer, uint64_t N);

        void (*read_string)(struct wasm_reader *wr, byte *string, uint64_t N);

        int32 (*read_int32)(struct wasm_reader *);

        int32 (*read_int32_from_leb128)(struct wasm_reader *);

        uint32 (*read_uint32)(struct wasm_reader *);

        uint32 (*read_uint32_from_leb128)(struct wasm_reader *);

        int64 (*read_int64)(struct wasm_reader *);

        int64 (*read_int64_from_leb128)(struct wasm_reader *);

        uint64 (*read_uint64)(struct wasm_reader *);

        uint64 (*read_uint64_from_leb128)(struct wasm_reader *);

        float32 (*read_float32)(struct wasm_reader *);

        float64 (*read_float64)(struct wasm_reader *);

        instruction (*read_instruction)(struct wasm_reader *);

        void (*read_instructions)(struct wasm_reader *, vec *);

        void (*close)(struct wasm_reader *);

        int (*index_check)(struct wasm_reader *, uint64);

    } wr_op;

    void (*free_segment[segment_count])(struct wasm_reader *, module *m);

    void (*decode_segment[segment_count])(struct wasm_reader *, module *m);

} wasm_reader;


wasm_reader *createWasmReader();

void destroy_wasm_reader(struct wasm_reader *wr);

void decode_module(wasm_reader *wr, module *m);

void free_module(wasm_reader *wr, module *m);

void register_segment_decode_op(wasm_reader *wr);

void register_segment_free_op(wasm_reader *wr);

#endif //WCASM_WASM_READER_H
