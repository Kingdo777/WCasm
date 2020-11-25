//
// Created by kingdo on 2020/11/25.
//

#include <stdlib.h>
#include <string.h>
#include "include/tool/vector/vector.h"

#define VEC_INIT_SIZE 8

uint64 get_size(vec *v) {
    return v->size;
}

uint64 get_cap(vec *v) {
    return v->cap;
}

void *get_ele(vec *v, uint64 index) {
    return v->start + index * v->element_size;
}

void *get_first_ele(vec *v) {
    return get_ele(v, 0);
}

void *get_last_ele(vec *v) {
    return get_ele(v, v->size - 1);
}

void append(vec *v, void *element) {
    if (v->size == v->cap) {
        v->cap *= 2;
        void *new = malloc(v->cap * v->element_size * 2);
        memcpy(new, v->start, v->size * v->element_size);
        free(v->start);
        v->start = new;
    }
    memcpy(v->start + v->size * v->element_size, element, v->element_size);
    v->size++;
}

void init_vec(vec *v, uint64 ele_size) {
    v->size = 0;
    v->cap = VEC_INIT_SIZE;
    v->element_size = ele_size;
    v->start = malloc(VEC_INIT_SIZE * ele_size);
    v->get_size = get_size;
    v->get_cap = get_cap;
    v->get_ele = get_ele;
    v->get_first_ele = get_first_ele;
    v->get_last_ele = get_last_ele;
    v->append = append;
}