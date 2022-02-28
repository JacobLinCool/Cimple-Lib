/**
 * @file array.h
 * @author JacobLinCool <jacoblincool@gmail.com> (github.com/JacobLinCool)
 * @brief The array header file of Jacob's Helper Library.
 * @version 2.0.0
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022 JacobLinCool (MIT License)
 *
 */
#ifndef JACOB_HELPER_ARRAY_H
#define JACOB_HELPER_ARRAY_H

#include "base.h"

#define array_map(array, length, func_return_type, func, args...) ({ \
    func_return_type* _result = (func_return_type*)calloc(length, sizeof(func_return_type)); \
    for (u64 i = 0; i < length; i++) { \
         _result[i] = func((array)[i], ##args); \
    } \
    _result; \
})

 /**
  * function arguments:
  * (accumulator, current value, current index, args...)
  */
#define array_reduce(array, length, func_return_type, func, args...) ({ \
    func_return_type _result = (func_return_type)0; \
    for (u64 i = 0; i < length; i++) { \
        _result = func(_result, (array)[i], i, ##args); \
    } \
    _result; \
})

#endif // JACOB_HELPER_ARRAY_H
