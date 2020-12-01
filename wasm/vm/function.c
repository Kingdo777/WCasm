//
// Created by kingdo on 2020/11/29.
//


#include <include/wasm/vm/vm.h>
#include <string.h>
#include <stdlib.h>

void linkExternalFunc(vm *v) {
    uint32 importSec_count = v->m->import_sec.import_segment_count;
    vec *func = &v->func;
    function f = {};
    import_pointer ip;
    type_index t_index, e_tIndex;
    module *e_m;
    export_pointer e_ep;
    func_index e_fIndex;
    for (uint32 i = 0; i < importSec_count; i++) {
        ip = v->m->import_sec.import_segment_addr + i;
        t_index = ip->im_desc.func;
        if (ip->im_desc.tag == func_im_export_tag) {
            if (!strcmp((const char *) ip->model_name, "env")) {
                /*本地函数*/
                f.code = NULL;
                f.tp = *(v->m->type_sec.type_segment_addr + t_index);
                f.native = get_native_function((const char *) ip->name);
            } else {
                /*外部wasm函数*/
                e_m = getModule((const char *) ip->model_name);
                for (int j = 0; j < e_m->export_sec.export_segment_count; ++j) {
                    e_ep = e_m->export_sec.export_segment_addr + i;
                    if (!strcmp((const char *) e_ep->name, (const char *) ip->name) &&
                        e_ep->ex_desc.tag == func_im_export_tag) {
                        e_fIndex = e_ep->ex_desc.index;
                        break;
                    }
                }
                e_tIndex = *(e_m->func_sec.func_segment_addr + e_fIndex);
                f.code = e_m->code_sec.code_segment_addr + e_fIndex;
                f.tp = *(e_m->type_sec.type_segment_addr + e_tIndex);
                f.native = NULL;
            }
        }
        func->append(func, &f);
    }
}

void linkInternalFunc(vm *v) {
    vec *func = &v->func;
    function f = {};
    uint32 internalFunc_count = v->m->func_sec.func_segment_count;
    for (uint32 i = 0; i < internalFunc_count; i++) {
        f.code = v->m->code_sec.code_segment_addr + i;
        type_index t_index = *(v->m->func_sec.func_segment_addr + i);
        f.tp = *(v->m->type_sec.type_segment_addr + t_index);
        f.native = NULL;
        func->append(func, &f);
    }
}

void initFunction(vm *v) {
    init_vec(&v->func, sizeof(function));
    linkExternalFunc(v);
    linkInternalFunc(v);
}

void freeFunction(vm *v) {
    free(v->func.start);
}