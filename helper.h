/**
 * @file helper.h
 * @author JacobLinCool (jacoblincool@gmail.com)
 * @brief A helper header file for C learners.
 * @version 1.0.0
 * @date 2022-01-11
 * @copyright Copyright (c) 2022 JacobLinCool (Released under the MIT License)
 */

#ifndef JACOB_HELPER_H
#define JACOB_HELPER_H

 // #region Include Common Header Files. Remember to use -lm flag when compiling.
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
// #endregion

// #region Type Alias for Standard Types.
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define f32 float
#define f64 double
#define f128 long double
// #endregion

// #region Function Macros for Cross-Type Number Operations.
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) > 0 ? (a) : -(a))
#define FLOOR(a) ((a) >= 0 ? (a) / 1 : ((a) - 1) / 1)
#define CEIL(a) ((a) >= 0 ? ((a) + 1) / 1 : (a) / 1)
#define ROUND(a) ((a) >= 0 ? ((a) + 0.5) / 1 : ((a) - 0.5) / 1)
// #endregion

// #region Function Macros for Array.
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARRAY_MAX(arr, idx) ({ \
    f128 _max = arr[0]; \
    i64 _idx = 0; \
    i64 _len = ARRAY_LENGTH(arr); \
    for (i64 i = 1; i < _len; i++) { \
        if (arr[i] > _max) { \
            _max = arr[i]; \
            _idx = i; \
        } \
    } \
    *idx = _idx; \
    arr[_idx]; \
})
#define ARRAY_MIN(arr, idx) ({ \
    f128 _min = arr[0]; \
    i64 _idx = 0; \
    i64 _len = ARRAY_LENGTH(arr); \
    for (i64 i = 1; i < _len; i++) { \
        if (arr[i] < _min) { \
            _min = arr[i]; \
            _idx = i; \
        } \
    } \
    *idx = _idx; \
    arr[_idx]; \
})
#define ARRAY_SUM(arr) ({ \
    f128 _sum = 0; \
    i64 _len = ARRAY_LENGTH(arr); \
    for (i64 i = 0; i < _len; i++) { \
        _sum += arr[i]; \
    } \
    _sum; \
})
#define ARRAY_AVG(arr) ({ \
    f128 _sum = 0; \
    i64 _len = ARRAY_LENGTH(arr); \
    for (i64 i = 0; i < _len; i++) { \
        _sum += arr[i]; \
    } \
    _sum / _len; \
})
// #endregion

// #region Function Macros for Debugging.
#define DEBUG_PRINT(fmt, ...) (DEBUG ? printf("\033[93m[DEBUG]\033[0m " fmt, ##__VA_ARGS__) : 0)
#define DEBUG_PRINT_ARRAY(arr, from, to) ({ \
    if (DEBUG) { \
        printf("\033[93m[DEBUG]\033[0m [ "); \
        for (i64 i = from; i < to; i++) { \
            printf("\033[96m%Lg\033[0m", (f128)arr[i]); \
            if (i != to - 1) { \
                printf(", "); \
            } \
        } \
        printf(" ]\n"); \
    } \
})
#define DEBUG_PRINT_MEMORY(ptr, from, to) ({ \
    if (DEBUG) { \
        for (i64 i = from; i < to; i++) { \
            void* addr = (u64*)ptr + i; \
            printf("\033[93m[DEBUG]\033[0m \033[95m%p\033[0m \033[93m%3" PRId64 "\033[0m [ ", addr, i); \
            u64 val = *(u64*)addr; \
            printf("\033[94m0x%016" PRIX64 "\033[0m (\033[96m%" PRIu64 "\033[0m) ]\n", val, val); \
        } \
    } \
})
// #endregion

// #region Function Macros for Execution Time Measurement.
#define TIME_START() ({ \
    struct timespec _start; \
    clock_gettime(CLOCK_MONOTONIC, &_start); \
    _start; \
})
#define TIME_CHECK(start) ({ \
    struct timespec _end; \
    clock_gettime(CLOCK_MONOTONIC, &_end); \
    f64 _diff = (_end.tv_sec - start.tv_sec) * 1e3 + (_end.tv_nsec - start.tv_nsec) / 1e6L; \
    _diff; \
})
// #endregion

#endif // JACOB_HELPER_H
// Any application that can be written in JavaScript, will eventually be written in JavaScript.
