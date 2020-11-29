//
// Created by kingdo on 2020/11/29.
//


#include <string.h>
#include <stdio.h>
#include <include/wasm/vm/vm.h>

void print_char(stack *pr_arg) {
    uint32 c = popU32(pr_arg);
    putchar(c);
}

nativeFunc get_native_function(const char *function_name) {
    if (!strcmp(function_name, "print_char")) {
        return print_char;
    }
    return NULL;
}