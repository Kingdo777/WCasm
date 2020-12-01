//
// Created by kingdo on 2020/11/27.
//

#ifndef WCASM_ERROR_HANDLE_H
#define WCASM_ERROR_HANDLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define errorExit(...) do{     \
        fprintf(stderr,  __VA_ARGS__);  \
        assert(0);                \
    }while(0)
#endif //WCASM_ERROR_HANDLE_H
