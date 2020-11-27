//
// Created by kingdo on 2020/11/27.
//

#include <stdlib.h>
#include "include/wasm/vm/vm.h"

void init_memory(module *module, memory *memory) {
    memory->limit = module->mem_sec.mem_segment_addr;
    memory->pageCount = memory->limit->min;
    memory->data = malloc(memory->pageCount * PAGE_SIZE);
}

void freeMemory(memory *memory) {
    if (memory->pageCount > 0 && memory->data != NULL)
        free(memory->data);
    memory->data = NULL;
    memory->pageCount = 0;
}

uint32 get_memoryCount(memory *memory) {
    return memory->pageCount;
}