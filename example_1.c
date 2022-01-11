// Copyright (c) JacobLinCool
#include "helper.h"
#define DEBUG 1

int main() {
    i64 arr[10] = { 0 };

    for (i32 i = 0; i < 10; i++) {
        arr[9 - i] = i * 20;
    }

    DEBUG_PRINT("arr[0] ~ arr[9]: \n");
    DEBUG_PRINT_ARRAY(arr, 0, 10);

    i32 max_idx = -1;
    i64 max = ARRAY_MAX(arr, &max_idx);
    DEBUG_PRINT("max: %" PRId64 ", max_idx: %d \n", max, max_idx);

    i32 min_idx = -1;
    i64 min = ARRAY_MIN(arr, &min_idx);
    DEBUG_PRINT("min: %" PRId64 ", min_idx: %d \n", min, min_idx);

    i64 sum = ARRAY_SUM(arr);
    DEBUG_PRINT("sum: %" PRId64 " \n", sum);

    i64 avg = ARRAY_AVG(arr);
    DEBUG_PRINT("avg: %" PRId64 " \n", avg);

    return 0;
}

// Any application that can be written in JavaScript, will eventually be written in JavaScript.
