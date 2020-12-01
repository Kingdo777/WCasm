//
// Created by kingdo on 2020/11/27.
//

#include <stdlib.h>
#include <string.h>
#include "include/wasm/vm/vm.h"


void initMemory(vm *v) {
    if (v->m->mem_sec.mem_segment_count > 0) {
        memory *memory = &v->memory;
        module *module = v->m;
        memory->limit = module->mem_sec.mem_segment_addr;
        memory->pageCount = memory->limit->min;
        memory->data = malloc(memory->pageCount * PAGE_SIZE);
        /*写入数据段的内容*/
        for (int i = 0; i < module->data_sec.data_segment_count; ++i) {
            data_pointer d = module->data_sec.data_segment_addr + i;
            execInst(v, &d->offset);
            uint64 offset = popU64(&v->operandStack);
            write_memory(memory, offset, d->init_data, d->init_data_count);
        }
    }
}

void freeMemory(vm *v) {
    if (v->m->mem_sec.mem_segment_count > 0) {
        memory *m = &v->memory;
        if (m->pageCount > 0 && m->data != NULL)
            free(m->data);
        m->data = NULL;
        m->pageCount = 0;
    }
}


uint32 get_memoryCount(memory *memory) {
    return memory->pageCount;
}

uint32 grow_memory(memory *m, uint32 n) {
    if (!PAGE_COUNT_CHECK(get_memoryCount(m) + n)) {
        return (int32) -1;
    }
    void *old_data = m->data;
    uint32 old_size = m->pageCount;
    m->pageCount += n;
    m->data = malloc(m->pageCount * PAGE_SIZE);
    memcpy(m->data, old_data, old_size * PAGE_SIZE);
    free(old_data);
    return old_size;
}

bool read_memory(memory *m, uint64 offset, byte *buf, uint64 buf_size) {
    if (!BOUNDARY_CHECK(m->pageCount * PAGE_SIZE, offset + buf_size)) {
        return false;
    }
    memcpy(buf, m->data + offset, buf_size);
    return true;
}

bool write_memory(memory *m, uint64 offset, byte *buf, uint64 buf_size) {
    if (!BOUNDARY_CHECK(m->pageCount * PAGE_SIZE, offset + buf_size)) {
        return false;
    }
    memcpy(m->data + offset, buf, buf_size);
    return true;
}