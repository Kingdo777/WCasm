//
// Created by kingdo on 2020/11/21.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <sys/mman.h>
#include <string.h>
#include <include/tool/leb128/leb128.h>
#include "include/wasm/wasm_reader/wasm_reader.h"

void wasm_reader_open(struct wasm_reader *wr, const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "open the wasm model fault:%s\n", filename);
        exit(0);
    }
    wr->wasm_model_fd = fd;
    wr->wasm_model_addr = mmap(NULL, MODEL_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
    wr->index = 0;
}

byte read_byte(struct wasm_reader *wr) {
    byte val = *(byte *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(byte);
    return val;
}

void read_N_byte(struct wasm_reader *wr, byte *buffer, uint64_t N) {
    memcpy(buffer, wr->wasm_model_addr, N);
    wr->index += (sizeof(byte) * N);
}

void read_string(struct wasm_reader *wr, byte *str, uint64_t N) {
    read_N_byte(wr, str, N);
    str[N] = '\0';
}

int32 read_int32(struct wasm_reader *wr) {
    int32 val = *(int32 *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(int32);
    return val;
}

int32 read_int32_from_leb128(struct wasm_reader *wr) {
    leb128_int32_t r;
    r = leb128_to_int32(wr->wasm_model_addr + wr->index);
    wr->index += r.len;
    return r.value;
}

uint32 read_uint32(struct wasm_reader *wr) {
    uint32 val = *(uint32 *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(uint32);
    return val;
}

uint32 read_uint32_from_leb128(struct wasm_reader *wr) {
    leb128_uint32_t r;
    r = leb128_to_uint32(wr->wasm_model_addr + wr->index);
    wr->index += r.len;
    return r.value;
}


int64 read_int64(struct wasm_reader *wr) {
    int64 val = *(int64 *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(int64);
    return val;
}

int64 read_int64_from_leb128(struct wasm_reader *wr) {
    leb128_int64_t r;
    r = leb128_to_int64(wr->wasm_model_addr + wr->index);
    wr->index += r.len;
    return r.value;
}

uint64 read_uint64(struct wasm_reader *wr) {
    uint64 val = *(uint64 *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(uint64);
    return val;
}

uint64 read_uint64_from_leb128(struct wasm_reader *wr) {
    leb128_uint64_t r;
    r = leb128_to_uint64(wr->wasm_model_addr + wr->index);
    wr->index += r.len;
    return r.value;
}

float32 read_float32(struct wasm_reader *wr) {
    float32 val = *(float32 *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(float32);
    return val;
}

float64 read_float64(struct wasm_reader *wr) {
    float64 val = *(float64 *) (wr->wasm_model_addr + wr->index);
    wr->index += sizeof(float64);
    return val;
}

void wasm_reader_close(struct wasm_reader *wr) {
    munmap(wr->wasm_model_addr, MODEL_SIZE);
    close(wr->wasm_model_fd);
}

int index_check(struct wasm_reader *wr, uint64 right_index) {
    return wr->index == right_index;
}

void register_wr_op(struct wasm_reader *wr) {
    wr->wr_op.open = wasm_reader_open;
    wr->wr_op.read_byte = read_byte;
    wr->wr_op.read_N_byte = read_N_byte;
    wr->wr_op.read_string = read_string;
    wr->wr_op.read_int32 = read_int32;
    wr->wr_op.read_int32_from_leb128 = read_int32_from_leb128;
    wr->wr_op.read_uint32 = read_uint32;
    wr->wr_op.read_uint32_from_leb128 = read_uint32_from_leb128;
    wr->wr_op.read_int64 = read_int64;
    wr->wr_op.read_int64_from_leb128 = read_int64_from_leb128;
    wr->wr_op.read_uint64 = read_uint64;
    wr->wr_op.read_uint64_from_leb128 = read_uint64_from_leb128;
    wr->wr_op.read_float32 = read_float32;
    wr->wr_op.read_float64 = read_float64;
    wr->wr_op.close = wasm_reader_close;
    wr->wr_op.index_check = index_check;
}

void init_wasm_reader_op(struct wasm_reader *wr) {
    register_wr_op(wr);
    register_segment_decode_op(wr);
    register_segment_free_op(wr);
}

wasm_reader *create_wasm_reader(module *m, const char *filename) {
    wasm_reader *wr = (wasm_reader *) malloc(sizeof(wasm_reader));
    wr->m = m;
    init_wasm_reader_op(wr);
    wr->wr_op.open(wr, filename);
    decode_module(wr);
    return wr;
}

void destroy_wasm_reader(struct wasm_reader *wr) {
    free_module(wr);
    wr->wr_op.close(wr);
    free(wr);
}