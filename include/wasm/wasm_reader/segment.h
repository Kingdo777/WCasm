//
// Created by kingdo on 2020/11/21.
//

#ifndef WCASM_SEGMENT_H
#define WCASM_SEGMENT_H

#include "include/tool/vector/vector.h"
#include "include/wasm/instruction/instruction.h"
#include "include/tool/type.h"
/*值类型*/
#define I32 0x7F
#define I64 0x7E
#define F32 0x7D
#define F64 0x7C
/*block type*/
#define BlockTypeI32 -1     // ()->(i32)
#define BlockTypeI64 -2     // ()->(i64)
#define BlockTypeF32 -3     // ()->(f32)
#define BlockTypeF64 -4     // ()->(f64)
#define BlockTypeEmpty -64  // ()->(f64)

/*表类型*/
#define table_func_type 0x70 /*函数*/

#define READ_SEGMENT(sec_type, sec_objName, segment_count_objName, segment_addr_objName, segment_eleName, sec_element_p_type_name, read_op, segment_name) do{\
            uint64 right_index = 0;                                     \
            sec_type *sec_name = &m->sec_objName;                   \
            uint64 sec_size = wr->wr_op.read_uint64_from_leb128(wr);   \
            right_index = sec_size + wr->index;                         \
            uint32 count = wr->wr_op.read_uint32_from_leb128(wr);          \
            sec_name->segment_count_objName = count;                    \
            sec_name->segment_addr_objName = malloc(sizeof(segment_eleName)*count);    \
            sec_element_p_type_name p;                                  \
            for (int i = 0; i < count; ++i) {                           \
                p = sec_name->segment_addr_objName + i;                 \
                read_op(wr, p);                                         \
            }                                                           \
            check_index(wr, right_index, "read_"segment_name" failure");\
        }while(0)

#define FREE_SEGMENT(sec_type, segment_count_name, segment_addr_name, free_op) do{ \
        for (int i = 0; i < m->sec_type.segment_count_name; ++i) {  \
            free_op(m->sec_type.segment_addr_name+i);           \
        }                                                               \
        if (m->sec_type.segment_addr_name != NULL)                  \
            free(m->sec_type.segment_addr_name);                    \
    }while(0)

/*表以及内存的限制*/
enum limit_tag {
    only_min,
    min_and_max
};
typedef struct {
    byte tag;
    uint32 min;
    uint32 max;
} limit;


/*魔数与版本号*/
#define MAGIC_NUMBER 0x6D736100 /*\0asm*/
#define VERSION 0x00000001

/*每个段的id*/
enum segment_id {
    custom_segment_id,
    type_segment_id,
    import_segment_id,
    func_segment_id,
    table_segment_id,
    mem_segment_id,
    global_segment_id,
    export_segment_id,
    start_segment_id,
    element_segment_id,
    code_segment_id,
    data_segment_id,
    segment_count
};

/*表达式*/
typedef instruction expr;

/*自定义段*/
typedef struct custom_segment {
    uint32 name_size;
    byte *name;
    byte *data;
    struct custom_segment *next;
} custom_segment;
/***
 * 类型段
 * 函数段其实是诸多函数类型的数组,因此这里定义成起指针
 * */
typedef struct func_type {
    /*参数类型数组,每种类型对应于一个值类型*/
    uint32 param_count;
    byte *param_types;
    /*返回值类型数组,每种类型对应于一个值类型*/
    uint32 return_count;
    byte *return_types;
} func_type, type, *type_pointer;
typedef struct {
    int type_segment_count;
    type_pointer type_segment_addr;
} type_segment;

/**
 * 函数-代码段
 * 函数段就是类型索引的数组
 * 代码段包括了局部变量的信息和字节码
 * */
typedef type_index func, *func_pointer;
typedef struct {
    uint32 func_segment_count;
    func_pointer func_segment_addr;
} func_segment;

typedef struct {
    uint32 count;
    byte type;
} local_var_info;
typedef struct {
    uint32 local_var_info_count;
    local_var_info *lv_info;/*局部变量的信息是通过数组来保存的*/
    uint64 code_size;
    vec inst;
} code, *code_pointer;
typedef struct {
    uint32 code_segment_count;
    code_pointer code_segment_addr;
} code_segment;
/**
 * 表-元素段
 * 表段就是表的数组,只能有一张表,表元素的类型只能是函数
 * 元素段存放了表的初始化数据,每个元素包含三部分:表索引,表内偏移,以及函数索引的列表(因为目前只支持安函数)
 * */
typedef struct {
    byte element_type;
    limit limit;
} tab, *table_pointer;
typedef struct {
    uint32 table_segment_count;
    table_pointer table_segment_addr;
} table_segment;

typedef struct {
    table_index table;
    expr offset;/*偏移是根据字节码计算的*/
    uint32 init_data_count;
    function_index *init_data;
} element, *element_pointer;
typedef struct {
    uint32 element_segment_count;
    element_pointer element_segment_addr;
} element_segment;

/**
 * 内存-数据段
 *
 *
 * */
typedef limit mem, *mem_pointer;
typedef struct {
    uint32 mem_segment_count;
    mem_pointer mem_segment_addr;
} mem_segment;

typedef struct {
    mem_index mem;
    expr offset;/*偏移是根据字节码计算的*/
    uint64 init_data_count;
    byte *init_data;
} data, *data_pointer;
typedef struct {
    uint32 data_segment_count;
    data_pointer data_segment_addr;
} data_segment;

/**
 * 全局段*/
enum val_mut_type {
    mut_const,  /*常量*/
    mut_var     /*变量*/
};
typedef struct {
    byte val_type;/*对应于四个值类型*/
    byte mut_type;
} global_type;
typedef struct {
    global_type type;
    expr init_data;
} global, *global_pointer;
typedef struct {
    uint32 global_segment_count;
    global_pointer global_segment_addr;
} global_segment;
/***
 * 导入-导出段
 * 可导入导出的有:
 *  函数      -> tag=0
 *  表       -> tag=1
 *  内存      -> tag=2
 *  全局变量    -> tag=3
 * */
enum im_export_tag {
    func_im_export_tag,
    table_im_export_tag,
    mem_im_export_tag,
    global_im_export_tag,
    im_export_tag_count
};
typedef struct {
    byte tag;
    union {
        func_index func;
        tab table;
        mem mem;
        global global;

    };
} import_desc;
typedef struct {
    byte *model_name;
    byte *name;
    import_desc im_desc;
} import, *import_pointer;
typedef struct {
    uint32 import_segment_count;
    import_pointer import_segment_addr;
} import_segment;

typedef struct {
    byte tag;
    uint32 index;
} export_desc;
typedef struct {
    byte *name;
    export_desc ex_desc;
} export, *export_pointer;
typedef struct {
    uint32 export_segment_count;
    export_pointer export_segment_addr;
} export_segment;
/*起始段*/
typedef function_index start, *start_pointer;
typedef struct {
    uint32 start_segment_count;
    start_pointer start_segment_addr;
} start_segment;

#endif //WCASM_SEGMENT_H
