//
// Created by kingdo on 2020/11/25.
//

#ifndef WCASM_VECTOR_H
#define WCASM_VECTOR_H

#include "include/tool/type.h"

typedef struct vec {
    uint64 cap;
    uint64 size;
    uint32 element_size;
    void *start;

    void (*append)(struct vec *, void *);

    uint64 (*get_size)(struct vec *);

    uint64 (*get_cap)(struct vec *);

    void *(*get_ele)(struct vec *, uint64);

    void *(*get_first_ele)(struct vec *);

    void *(*get_last_ele)(struct vec *);
} vec;

void init_vec(vec *v, uint64 ele_size);

#endif //WCASM_VECTOR_H
