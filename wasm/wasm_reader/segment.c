//
// Created by kingdo on 2020/11/21.
//

#include <include/tool/error/error_handle.h>
#include "include/wasm/wasm_reader/wasm_reader.h"
#include "include/wasm/wasm_reader/segment.h"

void decode_get_wrong(const char *info) {
    errorExit("decode module get wrong ,info:%s\n", info);
}

void check_index(wasm_reader *wr, uint64 right_index, const char *info) {
    if (!wr->wr_op.index_check(wr, right_index)) {
        errorExit("the wasm_bin index isn't right:%s\n", info);
    }
}


/**
 * 类型段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_type(wasm_reader *wr, type_pointer tp) {
    if (0x60 != wr->wr_op.read_byte(wr))
        decode_get_wrong("read type first byte isn't 0x60");
    tp->param_count = wr->wr_op.read_uint32_from_leb128(wr);
    if (tp->param_count) {
        tp->param_types = malloc(sizeof(byte) * tp->param_count);
        wr->wr_op.read_N_byte(wr, tp->param_types, tp->param_count);
    } else {
        tp->param_types = NULL;
    }

    tp->return_count = wr->wr_op.read_uint32_from_leb128(wr);
    if (tp->return_count) {
        tp->return_types = malloc(sizeof(byte) * tp->return_count);
        wr->wr_op.read_N_byte(wr, tp->return_types, tp->return_count);
    } else {
        tp->return_types = NULL;
    }

}

void free_type(type_pointer tp) {
    if (tp->param_count && tp->param_types != NULL)
        free(tp->param_types);
    if (tp->return_count && tp->return_types != NULL)
        free(tp->return_types);
}

void read_typeSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(type_segment, type_sec, type_segment_count,
                 type_segment_addr, type, type_pointer, read_type, "type_segment");
}

void free_typeSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(type_sec, type_segment_count, type_segment_addr, free_type);
}

/**
 * 函数段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_func(wasm_reader *wr, func_pointer fp) {
    *fp = wr->wr_op.read_uint32_from_leb128(wr);
}

void free_func(func_pointer fp) {
    if (NULL == fp)
        return;
}

void read_funcSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(func_segment, func_sec, func_segment_count,
                 func_segment_addr, func, func_pointer, read_func, "func_segment");
}

void free_funcSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(func_sec, func_segment_count, func_segment_addr, free_func);
}

/**
 * 表段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_limit(wasm_reader *wr, limit *l) {
    l->tag = wr->wr_op.read_byte(wr);
    l->min = wr->wr_op.read_uint32_from_leb128(wr);
    if (min_and_max == l->tag) {
        l->max = wr->wr_op.read_uint32_from_leb128(wr);
    }
}

void read_table(wasm_reader *wr, table_pointer tp) {
    tp->element_type = wr->wr_op.read_byte(wr);
    read_limit(wr, &tp->limit);
}

void free_table(table_pointer tp) {
    if (NULL == tp)
        return;
}

void read_tableSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(table_segment, table_sec, table_segment_count,
                 table_segment_addr, tableType, table_pointer, read_table, "table_segment");
}

void free_tableSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(table_sec, table_segment_count, table_segment_addr, free_table);
}

/**
 * 内存段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_mem(wasm_reader *wr, mem_pointer mp) {
    read_limit(wr, mp);
}

void free_mem(mem_pointer mp) {
    if (NULL == mp)
        return;
}

void read_memSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(mem_segment, mem_sec, mem_segment_count,
                 mem_segment_addr, mem, mem_pointer, read_mem, "mem_segment");
}

void free_memSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(mem_sec, mem_segment_count, mem_segment_addr, free_mem);
}

/**
 * 全局段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_expr(wasm_reader *wr, expr *ex) {
    *ex = wr->wr_op.read_instruction(wr);
    if (End_ != wr->wr_op.read_instruction(wr).op_code) {
        errorExit("wrong expr\n");
    }
}

void free_expr(expr *ex) {

}

void read_global(wasm_reader *wr, global_pointer gp) {
    gp->type.val_type = wr->wr_op.read_byte(wr);
    gp->type.mut_type = wr->wr_op.read_byte(wr);
    read_expr(wr, &gp->init_data);
}

void free_global(global_pointer gp) {
    free_expr(&gp->init_data);
}

void read_globalSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(global_segment, global_sec, global_segment_count,
                 global_segment_addr, global, global_pointer, read_global, "global_segment");
}

void free_globalSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(global_sec, global_segment_count, global_segment_addr, free_global);
}

/**
 * 导入段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_import(wasm_reader *wr, import_pointer ip) {
    int moduleName_size = wr->wr_op.read_uint32_from_leb128(wr);
    ip->model_name = malloc(moduleName_size + 1);
    wr->wr_op.read_string(wr, ip->model_name, moduleName_size);

    int name_size = wr->wr_op.read_uint32_from_leb128(wr);
    ip->name = malloc(name_size + 1);
    wr->wr_op.read_string(wr, ip->name, name_size);

    ip->im_desc.tag = wr->wr_op.read_byte(wr);
    switch (ip->im_desc.tag) {
        case func_im_export_tag:
            read_func(wr, &ip->im_desc.typeIndex);
            break;
        case table_im_export_tag:
            read_table(wr, &ip->im_desc.table);
            break;
        case mem_im_export_tag:
            read_mem(wr, &ip->im_desc.mem);
            break;
        case global_im_export_tag:
            read_global(wr, &ip->im_desc.global);
            break;
        default:
            decode_get_wrong("unknown im_desc.tag");
            break;
    }
}

void free_import(import_pointer ip) {
    if (ip->model_name != NULL)
        free(ip->model_name);
    if (ip->name != NULL)
        free(ip->name);
}

void read_importSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(import_segment, import_sec, import_segment_count,
                 import_segment_addr, import, import_pointer, read_import, "import_segment");
}

void free_importSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(import_sec, import_segment_count, import_segment_addr, free_import);
}

/**
 * 导出段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_export(wasm_reader *wr, export_pointer ep) {
    uint64 len = wr->wr_op.read_uint64_from_leb128(wr);
    ep->name = malloc(len + 1);
    wr->wr_op.read_string(wr, ep->name, len);
    ep->ex_desc.tag = wr->wr_op.read_byte(wr);
    ep->ex_desc.index = wr->wr_op.read_uint32_from_leb128(wr);
}

void free_export(export_pointer ep) {
    if (NULL != ep->name)
        free(ep->name);
}

void read_exportSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(export_segment, export_sec, export_segment_count,
                 export_segment_addr, export, export_pointer, read_export, "export_segment");
}

void free_exportSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(export_sec, export_segment_count, export_segment_addr, free_export);
}

/**
 * 起始段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_start(wasm_reader *wr, start_pointer sp) {
    /**
     * 所有的段中,只有其实段的个数是确定的,有则为1,没有则为0,因此镜像文件中没有记录,但是为了复用READ_SEGMENT宏函数,我们把start_pointer
     * 的值赋值给了start_segment_count,因此这里的read_start就是空操作了
     * */
}

void free_start(start_pointer sp) {
    if (NULL == sp)
        return;
}

void read_startSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(start_segment, start_sec, start_segment_count,
                 start_segment_addr, start, start_pointer, read_start, "start_segment");
    *m->start_sec.start_segment_addr = m->start_sec.start_segment_count;
    m->start_sec.start_segment_count = 1;
}

void free_startSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(start_sec, start_segment_count, start_segment_addr, free_start);
}

/**
 * 元素段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_element(wasm_reader *wr, element_pointer ep) {
    ep->table = wr->wr_op.read_uint32_from_leb128(wr);
    read_expr(wr, &ep->offset);
    ep->init_data_count = wr->wr_op.read_uint32_from_leb128(wr);
    ep->init_data = malloc(sizeof(func_index) * ep->init_data_count);
    for (int i = 0; i < ep->init_data_count; ++i) {
        ep->init_data[i] = wr->wr_op.read_uint32_from_leb128(wr);
    }
}

void free_element(element_pointer ep) {
    free_expr(&ep->offset);
    if (NULL != ep->init_data)
        free(ep->init_data);
}

void read_elementSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(element_segment, element_sec, element_segment_count,
                 element_segment_addr, element, element_pointer, read_element, "element_segment");
}

void free_elementSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(element_sec, element_segment_count, element_segment_addr, free_element);
}

/**
 * 代码段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_code(wasm_reader *wr, code_pointer cp) {
    uint64 right_index;
    uint64 code_size = wr->wr_op.read_uint64_from_leb128(wr);
    cp->code_size = code_size;
    right_index = wr->index + code_size;
    cp->local_var_info_count = wr->wr_op.read_uint32_from_leb128(wr);
    cp->lv_info = cp->local_var_info_count > 0 ? malloc(sizeof(local_var_info) * cp->local_var_info_count) : NULL;
    for (int i = 0; i < cp->local_var_info_count; ++i) {
        cp->lv_info[i].count = wr->wr_op.read_uint32_from_leb128(wr);
        cp->lv_info[i].type = wr->wr_op.read_byte(wr);
    }
    wr->wr_op.read_instructions(wr, &cp->inst);
    check_index(wr, right_index, "read_code");
}

void free_code(code_pointer cp) {
    struct vec *ex = &cp->inst;
    void *arg;
    for (uint64 i = 0; i < ex->size; i++) {
        arg = ((instruction *) ex->get_ele(ex, i))->arg;
        if (arg != NULL)
            free(arg);
    }
    free(ex->start);
}

void read_codeSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(code_segment, code_sec, code_segment_count,
                 code_segment_addr, code, code_pointer, read_code, "code_segment");
}

void free_codeSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(code_sec, code_segment_count, code_segment_addr, free_code);
}

/**
 * 数据段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */
void read_data(wasm_reader *wr, data_pointer dp) {
    dp->mem = wr->wr_op.read_uint32_from_leb128(wr);
    read_expr(wr, &dp->offset);
    dp->init_data_count = wr->wr_op.read_uint64_from_leb128(wr);
    dp->init_data = malloc(sizeof(byte) * dp->init_data_count);
    wr->wr_op.read_N_byte(wr, dp->init_data, dp->init_data_count);
}

void free_data(data_pointer dp) {
    free_expr(&dp->offset);
    if (dp->init_data != NULL)
        free(dp->init_data);
}

void read_dataSec(wasm_reader *wr, module *m) {
    READ_SEGMENT(data_segment, data_sec, data_segment_count,
                 data_segment_addr, data, data_pointer, read_data, "data_segment");
}

void free_dataSec(wasm_reader *wr, module *m) {
    FREE_SEGMENT(data_sec, data_segment_count, data_segment_addr, free_data);
}

/**
 * 自定义段解析
 * 保证此时的类型ID一定是正确的,读到的第一个字节一定是真个段的总长度
 * */

void read_customSec(wasm_reader *wr, module *m) {
    uint64 right_index;
    uint64 sec_size = wr->wr_op.read_uint64_from_leb128(wr);
    right_index = sec_size + wr->index;
    m->custom_sec = malloc(sizeof(struct custom_segment));
    m->custom_segment_count++;
    custom_segment *cs = m->custom_sec;
    cs->next = m->custom_sec->next;
    cs->name_size = wr->wr_op.read_uint32_from_leb128(wr);
    cs->name = malloc(cs->name_size + 1);
    wr->wr_op.read_string(wr, cs->name, cs->name_size);
    uint data_size = right_index - wr->index;
    cs->data = malloc(sizeof(byte) * data_size);
    wr->wr_op.read_N_byte(wr, cs->data, data_size);
    check_index(wr, right_index, "read custom_segment failure");
}

void free_customSec(wasm_reader *wr, module *m) {
    for (int i = 0; i < m->custom_segment_count; ++i) {
        custom_segment *cs = m->custom_sec->next;
        if (NULL != cs) {
            if (NULL != cs->name)
                free(cs->name);
            if (NULL != cs->data)
                free(cs->data);
            m->custom_sec->next = cs->next;
            free(cs);
        }
    }
}

void register_segment_decode_op(wasm_reader *wr) {
    for (int segment_i = 0; segment_i < segment_count; ++segment_i) {
        switch (segment_i) {
            case custom_segment_id:
                wr->decode_segment[segment_i] = read_customSec;
                break;
            case type_segment_id:
                wr->decode_segment[segment_i] = read_typeSec;
                break;
            case import_segment_id:
                wr->decode_segment[segment_i] = read_importSec;
                break;
            case func_segment_id:
                wr->decode_segment[segment_i] = read_funcSec;
                break;
            case table_segment_id:
                wr->decode_segment[segment_i] = read_tableSec;
                break;
            case mem_segment_id:
                wr->decode_segment[segment_i] = read_memSec;
                break;
            case global_segment_id:
                wr->decode_segment[segment_i] = read_globalSec;
                break;
            case export_segment_id:
                wr->decode_segment[segment_i] = read_exportSec;
                break;
            case start_segment_id:
                wr->decode_segment[segment_i] = read_startSec;
                break;
            case element_segment_id:
                wr->decode_segment[segment_i] = read_elementSec;
                break;
            case code_segment_id:
                wr->decode_segment[segment_i] = read_codeSec;
                break;
            case data_segment_id:
                wr->decode_segment[segment_i] = read_dataSec;
                break;
            default:
                errorExit("wrong segment_id\n");
        }
    }
}

void register_segment_free_op(wasm_reader *wr) {
    for (int segment_i = 0; segment_i < segment_count; ++segment_i) {
        switch (segment_i) {
            case custom_segment_id:
                wr->free_segment[segment_i] = free_customSec;
                break;
            case type_segment_id:
                wr->free_segment[segment_i] = free_typeSec;
                break;
            case import_segment_id:
                wr->free_segment[segment_i] = free_importSec;
                break;
            case func_segment_id:
                wr->free_segment[segment_i] = free_funcSec;
                break;
            case table_segment_id:
                wr->free_segment[segment_i] = free_tableSec;
                break;
            case mem_segment_id:
                wr->free_segment[segment_i] = free_memSec;
                break;
            case global_segment_id:
                wr->free_segment[segment_i] = free_globalSec;
                break;
            case export_segment_id:
                wr->free_segment[segment_i] = free_exportSec;
                break;
            case start_segment_id:
                wr->free_segment[segment_i] = free_startSec;
                break;
            case element_segment_id:
                wr->free_segment[segment_i] = free_elementSec;
                break;
            case code_segment_id:
                wr->free_segment[segment_i] = free_codeSec;
                break;
            case data_segment_id:
                wr->free_segment[segment_i] = free_dataSec;
                break;
            default:
                errorExit("wrong segment_id\n");
        }
    }
}