//
// Created by kingdo on 2020/11/21.
//

#ifndef WCASM_MODULE_H
#define WCASM_MODULE_H

#include "include/wasm/wasm_reader/segment.h"
#include "include/tool/type.h"

#define PAGE_SIZE (64*1024)
#define MAX_PAGE_COUNT (64*1024)

#define PAGE_COUNT_CHECK(N)     (MAX_PAGE_COUNT>(N))
#define BOUNDARY_CHECK(MAX, N)  ((MAX)>=(N))

typedef struct {
    mem *limit;
    uint64 pageCount;
    byte *data;
} memory;

typedef struct module {
    uint32 magic_number;
    uint32 version;
    int custom_segment_count;
    custom_segment *custom_sec;
    type_segment type_sec;
    import_segment import_sec;
    func_segment func_sec;
    table_segment table_sec;
    mem_segment mem_sec;
    global_segment global_sec;
    export_segment export_sec;
    start_segment start_sec;
    element_segment element_sec;
    code_segment code_sec;
    data_segment data_sec;

    const char *bin;
} module;

module *createModule(const char *bin);

#endif //WCASM_MODULE_H
