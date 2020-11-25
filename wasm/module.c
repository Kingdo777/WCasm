//
// Created by kingdo on 2020/11/22.
//

#include "include/wasm/wasm_reader/wasm_reader.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void get_magic_version_num(wasm_reader *wr) {
    if (MAGIC_NUMBER != wr->wr_op.read_uint32(wr)) {
        fprintf(stderr, "MAGIC_NUMBER is wrong\n");
        exit(0);
    }
    wr->m->magic_number = MAGIC_NUMBER;
    wr->m->version = wr->wr_op.read_uint32(wr);
}

void decode_module(wasm_reader *wr) {
    byte secID;
    byte current_secID = type_segment_id;
    get_magic_version_num(wr);
    wr->m->custom_segment_count = 0;
    wr->m->custom_sec = NULL;
    while (true) {
        secID = wr->wr_op.read_byte(wr);
        if (secID != custom_segment_id && secID < current_secID || secID >= segment_count) {
            fprintf(stderr, "secID get wrong\n");
            exit(0);
        }
        wr->decode_segment[secID](wr);
        current_secID = secID + 1;
        if (wr->index >= wr->model_size)
            break;
    }
}

void free_module(wasm_reader *wr) {
    for (int i = custom_segment_id; i < segment_count; ++i) {
        wr->free_segment[i](wr);
    }
}