//
// Created by kingdo on 2020/11/22.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/wasm/module.h"
#include "include/wasm/wasm_reader/wasm_reader.h"

module *createModule(const char *bin) {
    module *m = malloc(sizeof(module));
    memset(m, 0, sizeof(module));
    m->bin = bin;
    return m;
}

void get_magic_version_num(wasm_reader *wr, module *m) {
    if (MAGIC_NUMBER != wr->wr_op.read_uint32(wr)) {
        fprintf(stderr, "MAGIC_NUMBER is wrong\n");
        exit(0);
    }
    m->magic_number = MAGIC_NUMBER;
    m->version = wr->wr_op.read_uint32(wr);
}

void decode_module(wasm_reader *wr, module *m) {
    byte secID;
    byte current_secID = type_segment_id;
    wr->wr_op.open(wr, m->bin);
    get_magic_version_num(wr, m);
    m->custom_segment_count = 0;
    m->custom_sec = NULL;
    while (true) {
        secID = wr->wr_op.read_byte(wr);
        if (secID != custom_segment_id && secID < current_secID || secID >= segment_count) {
            fprintf(stderr, "secID get wrong\n");
            exit(0);
        }
        wr->decode_segment[secID](wr, m);
        current_secID = secID + 1;
        if (wr->index >= wr->model_size)
            break;
    }
}

void free_module(wasm_reader *wr, module *m) {
    for (int i = custom_segment_id; i < segment_count; ++i) {
        wr->free_segment[i](wr, m);
    }
    free(m);
}