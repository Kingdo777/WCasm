//
// Created by kingdo on 2020/11/21.
//

#ifndef WCASM_WASM_READER_H
#define WCASM_WASM_READER_H


#include "include/wasm/module.h"
#include "segment.h"
#include "include/tool/type.h"

#define MODEL_SIZE 128*1024*1024  //128MB

typedef struct wasm_reader {
    byte *wasm_model_addr;  /*mmap的内存地址*/
    uint64 index;           /*内存索引,记录当前解析的位置*/
    int wasm_model_fd;      /*二进制文件句柄*/

    module *m;              /*解析的模型*/
    void (*decode_segment[segment_count])(struct wasm_reader *);

    void (*free_segment[segment_count])(struct wasm_reader *);

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

        void (*close)(struct wasm_reader *);

        int (*index_check)(struct wasm_reader *, uint64);

    } wr_op;
} wasm_reader;


wasm_reader *create_wasm_reader(module *m, const char *filename);

void decode_module(wasm_reader *wr);

void destroy_wasm_reader(struct wasm_reader *wr);

void free_module(wasm_reader *wr);

void register_segment_decode_op(wasm_reader *wr);

void register_segment_free_op(wasm_reader *wr);

#endif //WCASM_WASM_READER_H
