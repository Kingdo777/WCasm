//
// Created by kingdo on 2020/11/29.
//

//
// Created by kingdo on 2020/11/27.
//

#include <stdlib.h>
#include <string.h>
#include "include/wasm/vm/vm.h"


void initTable(vm *v) {
    table *table = &v->table;
    module *module = v->m;
    table->tab = module->table_sec.table_segment_addr;
    if (table->tab->limit.tag == only_min) {
        table->itemCount = table->tab->limit.min;
    } else {
        table->itemCount = table->tab->limit.max;
    }
    table->item = malloc(table->itemCount * sizeof(func_index));
    /*写入元素段的内容*/
    for (int i = 0; i < module->element_sec.element_segment_count; ++i) {
        element_pointer ep = module->element_sec.element_segment_addr + i;
        execInst(v, &ep->offset);
        uint64 offset = popU64(&v->operandStack);
        for (int j = 0; j < ep->init_data_count; ++j) {
            setTable(table, offset + j, *(ep->init_data + j));
        }
    }
}

void freeTable(vm *v) {
    table *table = &v->table;
    if (table->itemCount > 0 && table->item != NULL)
        free(table->item);
    table->item = NULL;
    table->itemCount = 0;
}

uint32 get_tableCount(table *table) {
    return table->itemCount;
}

func_index getTable(table *t, uint32 index) {
    return t->item[index];
}

void setTable(table *t, uint32 index, func_index f_index) {
    t->item[index] = f_index;
}