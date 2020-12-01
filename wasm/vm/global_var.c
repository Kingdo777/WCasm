//
// Created by kingdo on 2020/11/29.
//

#include <include/wasm/vm/vm.h>
#include <stdlib.h>

void initGlobalVar(vm *v) {
    if (v->m->global_sec.global_segment_count > 0) {
        uint64 global_count = v->m->global_sec.global_segment_count;
        v->globalCount = global_count;
        v->globalVar = malloc(global_count * sizeof(uint64));
        for (int i = 0; i < global_count; ++i) {
            global_pointer gp = v->m->global_sec.global_segment_addr + i;
            execInst(v, &gp->init_data);
            *(v->globalVar + i) = popU64(&v->operandStack);
        }
    }
}

void freeGlobalVar(vm *v) {
    if (v->m->global_sec.global_segment_count > 0) {
        if (v->globalCount && NULL != v->globalVar)
            free(v->globalVar);
        v->globalCount = 0;
    }
}