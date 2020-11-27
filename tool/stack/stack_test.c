//
// Created by kingdo on 2020/11/27.
//

#include "include/wasm/vm/vm.h"
#include "include/tool/stack/stack.h"

bool stack_test(vm *v) {
    stack *s = &v->operandStack;
    bool a, a_ = false;
    uint32 b, b_ = 345;
    int32 c, c_ = -3465;
    uint64 d, d_ = 34535345345;
    int64 e, e_ = -243789234234;
    float32 f, f_ = 2323.535;
    byte h, h_ = 201;
    float64 g, g_ = 42343243.234234234;
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushF64(s, g_);
    pushBool(s, a_);
    pushU32(s, b_);
    pushS32(s, c_);
    pushU64(s, d_);
    pushS64(s, e_);
    pushF32(s, f_);
    pushF64(s, g_);
    pushByte(s, h_);
    h = popByte(s);
    g = popF64(s);
    f = popF32(s);
    e = popU64(s);
    d = popU64(s);
    c = popS32(s);
    b = popU32(s);
    a = popBool(s);
    if (a == a_)
        if (b == b_)
            if (c == c_)
                if (d == d_)
                    if (e == e_)
                        if (f == f_)
                            if (g == g_)
                                if (h == h_)
                                    return true;
    return false;
}