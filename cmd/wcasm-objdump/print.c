//
// Created by kingdo on 2020/11/24.
//
#include <stdbool.h>
#include "include/tool/error/error_handle.h"
#include "include/wasm/module.h"
#include "include/wasm/wasm_reader/segment.h"

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
            errorExit("\nwrong typeID\n");
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
                errorExit("\nwrong typeID\n");
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
    element_pointer ep;
    uint32 offset;
    for (int i = 0; i < sec.element_segment_count; ++i) {
        ep = sec.element_segment_addr + i;
        offset = *(uint32 *) (ep->offset.arg);
        printf("  - element[%d] table=0 offset=%d count=%d\n", i, offset, ep->init_data_count);
        for (int j = 0; j < ep->init_data_count; ++j) {
            printf("   - ele[%d] =func[%d]\n", j + offset, *(uint32 *) (ep->init_data + j));
        }
    }
}

void print_instructions(vec *instructions, int format_blank_count, bool format_is_block);

void print_instruction(instruction *inst, int format_blank_count);

void print_instruction(instruction *inst, int format_blank_count) {
    printf("%s ", getOpName(inst));
    void *arg = inst->arg;
    blockArgs *blockArgs1;
    ifArgs *ifArgs1;
    brArgs *brArgs1;
    brTableArgs *brTableArgs1;
    callArgs *callArgs1;
    call_indirectArgs *callIndirectArgs1;
    memArgs *memArgs1;
    if (NULL != arg) {
        switch (inst->op_code) {
            case Block:
            case Loop:
                blockArgs1 = (blockArgs *) arg;
                switch (((blockArgs *) arg)->blockType) {
                    case -1:
                        printf("i32\n");
                        break;
                    case -2:
                        printf("i64\n");
                        break;
                    case -3:
                        printf("f32\n");
                        break;
                    case -4:
                        printf("f64\n");
                        break;
                    case -64:
                        printf("\n");
                        break;
                    default:
                        break;
                }
                print_instructions(&blockArgs1->instructions, format_blank_count + 2, true);
                break;
            case If:
                ifArgs1 = (ifArgs *) arg;
                switch (((blockArgs *) arg)->blockType) {
                    case -1:
                        printf("i32\n");
                        break;
                    case -2:
                        printf("i64\n");
                        break;
                    case -3:
                        printf("f32\n");
                        break;
                    case -4:
                        printf("f64\n");
                        break;
                    case -64:
                        printf("\n");
                        break;
                    default:
                        break;
                }
                print_instructions(&ifArgs1->instructions1, format_blank_count + 2, true);
                print_instructions(&ifArgs1->instructions2, format_blank_count + 2, true);
                break;
            case Br:
            case BrIf:
                brArgs1 = (brArgs *) arg;
                printf("%u\n", *brArgs1);
                break;
            case BrTable:
                brTableArgs1 = (brTableArgs *) arg;
                for (int i = 0; i < brTableArgs1->labelCount; ++i) {
                    printf("%u ", *(brTableArgs1->labels + i));
                }
                printf("%u(default)", brTableArgs1->defaultLabels);
                printf("\n");
                break;
            case Call:
                callArgs1 = (callArgs *) arg;
                printf("%u\n", *callArgs1);
                break;
            case CallIndirect:
                callIndirectArgs1 = (call_indirectArgs *) arg;
                printf("index:%u table:0x0\n", callIndirectArgs1->index);
                break;
            case LocalGet:
            case LocalSet:
            case LocalTee:
            case GlobalGet:
            case GlobalSet:
                printf("%u\n", *(uint32 *) arg);
                break;
            case MemorySize:
            case MemoryGrow:
                printf("0x0\n");
                break;
            case I32Const:
                printf("%d\n", *(int32 *) arg);
                break;
            case I64Const:
                printf("%ld\n", *(int64 *) arg);
                break;
            case F32Const:
                printf("%.2f\n", *(float32 *) arg);
                break;
            case F64Const:
                printf("%.2f\n", *(float64 *) arg);
                break;
            case TruncSat:
                printf("%d\n", *(truncSatArgs *) arg);
                break;
            default:
                if (I32Load <= inst->op_code && inst->op_code <= I64Store32) {
                    memArgs1 = (memArgs *) arg;
                    printf("align=%u offset=%lu\n", memArgs1->align, memArgs1->offset);
                    break;
                }
        }
    } else {
        printf("\n");
    }
}

void print_instructions(vec *instructions, int format_blank_count, bool format_is_block) {
    for (int i = 0; i < instructions->size; ++i) {
        printf("             ");
        if (format_is_block && i == instructions->size - 1) {
            for (int j = 0; j < format_blank_count - 2; ++j) {
                printf(" ");
            }
        } else {
            for (int j = 0; j < format_blank_count; ++j) {
                printf(" ");
            }
        }
        print_instruction((instruction *) (instructions->get_ele(instructions, i)), format_blank_count);
    }
}

void print_code_segment_info(code_segment sec) {
    code_pointer code_segment_addr;
    for (int i = 0; i < sec.code_segment_count; ++i) {
        code_segment_addr = sec.code_segment_addr + i;
        printf("  - code[%d]: size=%lu\n", i, code_segment_addr->code_size);
        print_instructions(&code_segment_addr->inst, 0, false);
    }
}

void print_data_segment_info(data_segment sec) {
    data_pointer dp;
    uint64 offset;
    for (int i = 0; i < sec.data_segment_count; ++i) {
        dp = sec.data_segment_addr + i;
        offset = *(uint32 *) (dp->offset.arg);
        printf("  - data[%d] memory=0 offset=%lu count=%lu: \n", i, offset, dp->init_data_count);
        for (int j = 0; j <= dp->init_data_count / 8; ++j) {
            printf("    ");
            for (int k = 0; k < 8; ++k) {
                uint64 index = j * 8 + k;
                if (index < dp->init_data_count) printf("%x ", *(dp->init_data + index)); else break;
            }
            printf("-> [");
            for (int k = 0; k < 8; ++k) {
                uint64 index = j * 8 + k;
                if (index < dp->init_data_count) printf("%c", *(dp->init_data + index)); else break;
            }
            printf("]");
            printf("\n");
        }
    }
}