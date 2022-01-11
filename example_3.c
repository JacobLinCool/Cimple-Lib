// Copyright (c) JacobLinCool
#include "helper.h"
#define DEBUG 1

int main() {
    i64 arr[10] = { 0 };

    for (i32 i = 0; i < 10; i++) {
        arr[9 - i] = i * 16;
    }

    DEBUG_PRINT("arr[0] ~ arr[9]: \n");
    DEBUG_PRINT_ARRAY(arr, 0, 10);

    DEBUG_PRINT("Memory Layout: \n");
    DEBUG_PRINT_MEMORY(arr, -1, 11);

    i64* arr_malloc = (i64*)malloc(sizeof(i64) * 10);

    for (i32 i = 0; i < 10; i++) {
        arr_malloc[9 - i] = i * 16;
    }

    DEBUG_PRINT("arr_malloc[0] ~ arr_malloc[9]: \n");
    DEBUG_PRINT_ARRAY(arr_malloc, 0, 10);

    DEBUG_PRINT("Memory Layout: \n");
    DEBUG_PRINT_MEMORY(arr_malloc, -1, 11);

    free(arr_malloc);

    return 0;
}

// Any application that can be written in JavaScript, will eventually be written in JavaScript.
