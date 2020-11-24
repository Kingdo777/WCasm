//
// Created by kingdo on 2020/11/24.
//

#include <include/wasm/module.h>
#include <stdio.h>
#include <cmd/wcasm-objdump/include/print.h>
#include "dump.h"

void wcasm_objdump(module *m) {
    printf("KINGDO WCasm （づ￣3￣）づ╭❤～\n");
    printf("version: %d\n\nSegment Info :\n", m->version);
    print_segment_info(m);
}