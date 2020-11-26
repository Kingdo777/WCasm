//
// Created by kingdo on 2020/11/21.
//

#ifndef WCASM_TYPE_H
#define WCASM_TYPE_H

#include <stdint.h>
#include <stdbool.h>

typedef unsigned char byte;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef float float32;
typedef double float64;

/*每个段内部索引*/
typedef uint32 type_index, func_index, table_index, mem_index, global_index;


#endif //WCASM_TYPE_H
