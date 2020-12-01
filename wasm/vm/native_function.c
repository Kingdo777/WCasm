//
// Created by kingdo on 2020/11/29.
//


#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "include/tool/error/error_handle.h"
#include "include/wasm/vm/vm.h"

void print_char(stack *pr_arg) {
    uint32 c = popU32(pr_arg);
    putchar(c);
}

void assert_true(stack *pr_arg) {
    assert(popBool(pr_arg) == true);
}

void assert_false(stack *pr_arg) {
    assert(popBool(pr_arg) == false);
}

void assert_eq_i32(stack *pr_arg) {
    assert(popU32(pr_arg) == popU32(pr_arg));
}

void assert_eq_i64(stack *pr_arg) {
    assert(popU64(pr_arg) == popU64(pr_arg));
}

void assert_eq_f32(stack *pr_arg) {
    assert(popF32(pr_arg) == popF32(pr_arg));
}

void assert_eq_f64(stack *pr_arg) {
    assert(popF64(pr_arg) == popF64(pr_arg));
}

nativeFunc get_native_function(const char *function_name) {
    if (!strcmp(function_name, "print_char")) {
        return print_char;
    } else if (!strcmp(function_name, "assert_true")) {
        return assert_true;
    } else if (!strcmp(function_name, "assert_false")) {
        return assert_false;
    } else if (!strcmp(function_name, "assert_eq_i32")) {
        return assert_eq_i32;
    } else if (!strcmp(function_name, "assert_eq_i64")) {
        return assert_eq_i64;
    } else if (!strcmp(function_name, "assert_eq_f32")) {
        return assert_eq_f32;
    } else if (!strcmp(function_name, "assert_eq_f64")) {
        return assert_eq_f64;
    } else {
        errorExit("unknown native function");
    }
    return NULL;
}