/**
 * @file format.h
 * @author JacobLinCool <jacoblincool@gmail.com> (github.com/JacobLinCool)
 * @brief The format header file of Jacob's Helper Library.
 * @version 2.0.0
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022 JacobLinCool (MIT License)
 *
 */
#ifndef JACOB_HELPER_FORMAT_H
#define JACOB_HELPER_FORMAT_H

#include "base.h"
#include "array.h"
#include "string.h"

 /**
  * @brief Tint the string.
  *
  * @param str The string to be tinted.
  * @param color The color of the string.
  * @return string The tinted string.
  */
static inline string tint(const string restrict str, const string restrict color) {
    string tinted = (string)malloc((strlen(str) + strlen(color) + 4 + 1) * sizeof(char));
    strcpy(tinted, color);
    strcat(tinted, str);
    strcat(tinted, CLR_NONE);
    return tinted;
}

#define PRIchar "c"
#define PRIstr "s"
#define PRIf32 "g"
#define PRIf64 "lg"
#define PRIf128 "Lg"
#define PRIptr "p"

#define format_array(type, array, from, to) ({ \
    u64 _len = to - from + 1; \
    string* _vals = (string*)malloc(_len * sizeof(string)); \
    i32 _max_len = 0; \
    for (i64 i = 0; i < _len; i++) { \
        asprintf(_vals + i, "%" PRI##type, array[i]); \
        _max_len = strlen(_vals[i]) > _max_len ? strlen(_vals[i]) : _max_len; \
    } \
    string* _strs = (string*)malloc(_len * sizeof(string)); \
    for (i64 i = 0; i < _len; i++) { \
        asprintf(_strs + i, "%s%4" PRIi64 " (%p) | " CLR_YELLOW "%*s" CLR_NONE, i == 0 ? CLR_MAGENTA : "", i, array + i, _max_len, _vals[i]); \
        free(_vals[i]); \
    } \
    free(_vals); \
    string _str = join(_strs, _len, "\n"); \
    for (i64 i = 0; i < _len; i++) { \
        free(_strs[i]); \
    } \
    free(_strs); \
    _str; \
})

#endif // JACOB_HELPER_FORMAT_H
