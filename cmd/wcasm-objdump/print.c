//
// Created by kingdo on 2020/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "print.h"

#include"include/wasm/module.h"
#include"include/wasm/wasm_reader/segment.h"

#define P_SEC_NAME_AND_COUNT(segment_count, sec_display) do{ \
        if(segment_count)                                   \
            printf("%s[%d]:\n", sec_display,segment_count);\
    }while(0)

void print_type_segment_info(type_segment sec);

void print_data_segment_info(data_segment sec);

void print_code_segment_info(code_segment sec);

void print_element_segment_info(element_segment sec);

void print_start_segment_info(start_segment sec);

void print_export_segment_info(export_segment sec);

void print_global_segment_info(global_segment sec);

void print_mem_segment_info(mem_segment sec);

void print_table_segment_info(table_segment sec);

void print_func_segment_info(func_segment sec);

void print_import_segment_info(import_segment sec);

void print_segment_info(module *m) {
    for (int secId = type_segment_id; secId < segment_count; ++secId) {
        switch (secId) {
            case type_segment_id:
                P_SEC_NAME_AND_COUNT (m->type_sec.type_segment_count, "Type");
                print_type_segment_info(m->type_sec);
                break;
            case import_segment_id:
                P_SEC_NAME_AND_COUNT (m->import_sec.import_segment_count, "Import");
                print_import_segment_info(m->import_sec);
                break;
            case func_segment_id:
                P_SEC_NAME_AND_COUNT (m->func_sec.func_segment_count, "Func");
                print_func_segment_info(m->func_sec);
                break;
            case table_segment_id:
                P_SEC_NAME_AND_COUNT (m->table_sec.table_segment_count, "Table");
                print_table_segment_info(m->table_sec);
                break;
            case mem_segment_id:
                P_SEC_NAME_AND_COUNT (m->mem_sec.mem_segment_count, "Mem");
                print_mem_segment_info(m->mem_sec);
                break;
            case global_segment_id:
                P_SEC_NAME_AND_COUNT (m->global_sec.global_segment_count, "Global");
                print_global_segment_info(m->global_sec);
                break;
            case export_segment_id:
                P_SEC_NAME_AND_COUNT (m->export_sec.export_segment_count, "Export");
                print_export_segment_info(m->export_sec);
                break;
            case start_segment_id:
                P_SEC_NAME_AND_COUNT (m->start_sec.start_segment_count, "Start");
                print_start_segment_info(m->start_sec);
                break;
            case element_segment_id:
                P_SEC_NAME_AND_COUNT (m->element_sec.element_segment_count, "Element");
                print_element_segment_info(m->element_sec);
                break;
            case code_segment_id:
                P_SEC_NAME_AND_COUNT (m->code_sec.code_segment_count, "Code");
                print_code_segment_info(m->code_sec);
                break;
            case data_segment_id:
                P_SEC_NAME_AND_COUNT (m->data_sec.data_segment_count, "Data");
                print_data_segment_info(m->data_sec);
                break;
            default:
                break;
        }
    }
    if (m->custom_segment_count) {
        P_SEC_NAME_AND_COUNT(m->custom_segment_count, "Custom");
        custom_segment *cs;
        for (int i = 0; i < m->custom_segment_count; ++i) {
            cs = m->custom_sec + i;
            printf("  - name:%s", cs->name);
        }
    }
}

const char *val_type(byte typeID) {
    switch (typeID) {
        case I32:
            return "i32";
        case I64:
            return "i64";
        case F32:
            return "f32";
        case F64:
            return "f64";
        default:
            fprintf(stderr, "\nwrong typeID\n");
            exit(0);
    }
}

void print_type_segment_info(type_segment sec) {
    type_pointer type_segment_addr;
    for (int i = 0; i < sec.type_segment_count; ++i) {
        type_segment_addr = sec.type_segment_addr + i;
        printf("  - type[%d]:", i);
        printf("(");
        for (int j = 0; j < type_segment_addr->param_count; ++j) {
            if (j)printf(",");
            printf("%s", val_type(*(type_segment_addr->param_types + j)));
        }
        printf(")->(");
        for (int j = 0; j < type_segment_addr->return_count; ++j) {
            if (j)printf(",");
            printf("%s", val_type(*(type_segment_addr->return_types + j)));
        }
        printf(")\n");
    }
}

void print_import_segment_info(import_segment sec) {
    char type_symbol[im_export_tag_count][10] = {
            "func",
            "table",
            "mem",
            "global",
    };
    import_pointer import_segment_addr;
    for (int i = 0; i < sec.import_segment_count; ++i) {
        import_segment_addr = sec.import_segment_addr + i;
        printf("  - import[%d]: %s <%s> <- %s.%s\n", i, type_symbol[import_segment_addr->im_desc.tag],
               import_segment_addr->name,
               import_segment_addr->model_name, import_segment_addr->name);
    }
}

void print_func_segment_info(func_segment sec) {
    func_pointer func_segment_addr;
    for (int i = 0; i < sec.func_segment_count; ++i) {
        func_segment_addr = sec.func_segment_addr + i;
        printf("  - func[%d]: typeId=%d\n", i, *func_segment_addr);
    }
}

void print_table_segment_info(table_segment sec) {
    table_pointer table_segment_addr;
    for (int i = 0; i < sec.table_segment_count; ++i) {
        table_segment_addr = sec.table_segment_addr + i;
        printf("  - table[%d]: type=funcref ", i);
        printf("min=%d", table_segment_addr->limit.min);
        if (table_segment_addr->limit.tag == min_and_max)
            printf(" max=%d", table_segment_addr->limit.max);
        puts("");
    }
}

void print_mem_segment_info(mem_segment sec) {
    mem_pointer mem_segment_addr;
    for (int i = 0; i < sec.mem_segment_count; ++i) {
        mem_segment_addr = sec.mem_segment_addr + i;
        printf("  - memory[%d]: pages ", i);
        printf("min=%d", mem_segment_addr->min);
        if (mem_segment_addr->tag == min_and_max)
            printf(" max=%d", mem_segment_addr->max);
        puts("");
    }
}

void print_global_segment_info(global_segment sec) {
    global_pointer global_segment_addr;
    for (int i = 0; i < sec.global_segment_count; ++i) {
        global_segment_addr = sec.global_segment_addr + i;
        printf("  - global[%d]: %s mutable=%d - init %s=", i, val_type(global_segment_addr->type.val_type),
               global_segment_addr->type.mut_type, val_type(global_segment_addr->type.val_type));
        switch (global_segment_addr->type.val_type) {
            case I32:
                printf("%d\n", *(int32 *) global_segment_addr->init_data.arg);
                break;
            case I64:
                printf("%ld\n", *(int64 *) global_segment_addr->init_data.arg);
                break;
            case F32:
                printf("%f\n", *(float32 *) global_segment_addr->init_data.arg);
                break;
            case F64:
                printf("%f\n", *(float64 *) global_segment_addr->init_data.arg);
                break;
            default:
                fprintf(stderr, "\nwrong typeID\n");
                exit(0);
        }
    }
}

void print_export_segment_info(export_segment sec) {
    export_pointer export_segment_addr;
    char type_symbol[im_export_tag_count][10] = {
            "func",
            "table",
            "mem",
            "global",
    };
    for (int i = 0; i < sec.export_segment_count; ++i) {
        export_segment_addr = sec.export_segment_addr + i;
        printf("  - export[%d]: %s[%d] -> %s\n", i, type_symbol[export_segment_addr->ex_desc.tag],
               export_segment_addr->ex_desc.index, export_segment_addr->name);
    }
}

void print_start_segment_info(start_segment sec) {
    start_pointer start_segment_addr;
    for (int i = 0; i < sec.start_segment_count; ++i) {
        start_segment_addr = sec.start_segment_addr + i;
        printf("  - start[%d]: %d\n", i, *start_segment_addr);
    }
}

void print_element_segment_info(element_segment sec) {
    element_pointer element_segment_addr;
    for (int i = 0; i < sec.element_segment_count; ++i) {
        element_segment_addr = sec.element_segment_addr + i;
        printf("  - element[%d]: \n", i);
        //#TODO 解析element
    }
}

void print_code_segment_info(code_segment sec) {
    code_pointer code_segment_addr;
    for (int i = 0; i < sec.code_segment_count; ++i) {
        code_segment_addr = sec.code_segment_addr + i;
        printf("  - code[%d]: size=%lu\n", i, code_segment_addr->code_size);
        //#TODO 解析code
    }
}

void print_data_segment_info(data_segment sec) {
    data_pointer data_segment_addr;
    for (int i = 0; i < sec.data_segment_count; ++i) {
        data_segment_addr = sec.data_segment_addr + i;
        printf("  - data[%d]: \n", i);
        //#TODO 解析data
    }
}