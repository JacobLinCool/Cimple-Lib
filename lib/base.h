/**
 * @file base.h
 * @author JacobLinCool <jacoblincool@gmail.com> (github.com/JacobLinCool)
 * @brief The base header file of Jacob's Helper Library.
 * @version 2.0.0
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022 JacobLinCool (MIT License)
 *
 */
#ifndef JACOB_HELPER_BASE_H
#define JACOB_HELPER_BASE_H

 // #region Include Common Header Files. Remember to use -lm flag when compiling.
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <regex.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #endregion

// #region Type Alias for Standard Types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef long double f128;
typedef char* string;
// #endregion

// #region ANSI Escape Colors.
#define CLR_RED     "\x1b[91m"
#define CLR_GREEN   "\x1b[92m"
#define CLR_YELLOW  "\x1b[93m"
#define CLR_BLUE    "\x1b[94m"
#define CLR_MAGENTA "\x1b[95m"
#define CLR_CYAN    "\x1b[96m"
#define CLR_NONE    "\x1b[0m"
// #endregion

#endif // JACOB_HELPER_BASE_H
