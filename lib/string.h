/**
 * @file string.h
 * @author JacobLinCool <jacoblincool@gmail.com> (github.com/JacobLinCool)
 * @brief The string header file of Jacob's Helper Library.
 * @version 2.0.0
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022 JacobLinCool (MIT License)
 *
 */
#ifndef JACOB_HELPER_STR_H
#define JACOB_HELPER_STR_H

#include "base.h"

 // #region trim
#define TRIM_LEFT 1
#define TRIM_RIGHT 2
#define _TRIM_2(target, mode, ...) trim(target, mode, "\t\n\r ")
#define _TRIM_1(target, ...) _TRIM_2(target, TRIM_LEFT | TRIM_RIGHT)
#define _TRIM_SELECTOR(arg1, arg2, arg3, arg4, ...) arg4
#define TRIM(target, args...) _TRIM_SELECTOR(target, ##args, trim, _TRIM_2, _TRIM_1)(target, ##args)

 /**
  * @brief Trim the string.
  *
  * @param target The string to be trimmed.
  * @param mode The trim mode. 3: both side, 1: left side, 2: right side.
  * @param dict The trim dictionary.
  * @return string The trimmed string.
  */
static inline string trim(const string restrict target, const u8 mode, const string restrict dict) {
    string trimmed = (string)calloc(strlen(target) + 1, sizeof(char));

    u64 left_offset = 0, right_offset = 0;
    if (mode & TRIM_LEFT) {
        left_offset = strspn(target, dict);
    }
    if (mode & TRIM_RIGHT) {
        for (u64 i = strlen(target) - 1; i >= 0; i--) {
            if (strchr(dict, target[i])) {
                right_offset++;
            }
            else {
                break;
            }
        }
    }

    strncpy(trimmed, target + left_offset, strlen(target) - left_offset - right_offset);
    trimmed[strlen(target) - left_offset - right_offset] = '\0';

    return trimmed;
}
// #endregion

// #region split
#define _SPLIT_2(target, count, ...) split(target, count, (string[]){" "}, 1)
#define _SPLIT_SELECTOR(arg1, arg2, arg3, arg4, ...) arg4
#define SPLIT(target, count, args...) _SPLIT_SELECTOR(0, ##args, split, 0, _SPLIT_2)(target, count, ##args)

/**
 * @brief Split the string into slices by the given delimiter strings.
 *
 * @param target The string to be splitted.
 * @param count The number of slices. This is a return value.
 * @param delimiters The delimiter strings.
 * @param delimiter_count The number of delimiter strings.
 * @return string* The slices.
 */
static inline string* split(const string restrict target, u64* restrict count, string* restrict delimiters, const u64 delimiter_count) {
    for (u64 i = 0; i < delimiter_count; i++) {
        if (delimiters[i] == NULL || strlen(delimiters[i]) == 0) {
            string r = (string)calloc(strlen(target) + 1, sizeof(char));
            strcpy(r, target);
            string* result = (string*)malloc(1 * sizeof(string));
            result[0] = r;
            *count = 1;
            return result;
        }
    }
    string head = (string)target;
    string* result = (string*)calloc(strlen(target) + 1, sizeof(string));
    u64 result_count = 0;

    while (true) {
        u64 window = UINT64_MAX, delimiter_length = 0;
        for (u64 i = 0; i < delimiter_count; i++) {
            string p = strstr(head, delimiters[i]);
            if (p != NULL && (p - head) < window) {
                window = p - head;
                delimiter_length = strlen(delimiters[i]);
            }
        }

        if (window == UINT64_MAX) {
            result[result_count++] = (string)malloc((strlen(head) + 1) * sizeof(char));
            strcpy(result[result_count - 1], head);
            break;
        }

        if (window != 0) {
            result[result_count++] = (string)malloc((window + 1) * sizeof(char));
            strncpy(result[result_count - 1], head, window);
            result[result_count - 1][window] = '\0';
        }

        head += window + delimiter_length;
    }

    *count = result_count;
    result = (string*)realloc(result, result_count * sizeof(string));
    return result;
}
// #endregion

// #region join
#define _JOIN_2(slices, count) join(slices, count, " ");
#define _JOIN_SELECTOR(arg1, arg2, arg3, ...) arg3
#define JOIN(slices, count, args...) _JOIN_SELECTOR(0, ##args, join, _JOIN_2)(slices, count, ##args)

/**
 * @brief Join the slices into a string.
 *
 * @param slices The slices.
 * @param count The number of slices.
 * @param glue The glue string.
 * @return string The joined string.
 */
static inline string join(string* restrict slices, const u64 count, const string restrict glue) {
    if (count == 0) {
        return (string)calloc(1, sizeof(char));
    }

    u64 length = strlen(glue) * count;
    for (u64 i = 0; i < count; i++) {
        length += strlen(slices[i]);
    }

    string joined = (string)calloc(length + 1, sizeof(char));
    strcpy(joined, slices[0]);

    for (u64 i = 1; i < count; i++) {
        strcat(joined, glue);
        strcat(joined, slices[i]);
    }

    return joined;
}
// #endregion

// #region replace

/**
 * @brief Replace the string with the given keyword and replacement.
 *
 * @param target The string to be replaced.
 * @param keyword The keyword to be replaced.
 * @param replacement The replacement.
 * @return string The replaced string.
 */
static inline string replace(const string restrict target, const string restrict keyword, const string restrict replacement) {
    u64 size = 0;
    string* slices = split(target, &size, (string[]) { (string)keyword }, 1);
    string joined = join(slices, size, replacement);
    free(slices);

    return joined;
}
// #endregion

#endif // JACOB_HELPER_STR_H
