/**
 * @file string.h
 * @author JacobLinCool <hi@jacoblin.cool> (github.com/JacobLinCool)
 * @brief The string header file of Cimple Lib.
 * @version 3.0.0
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022 JacobLinCool (MIT License)
 * @see https://github.com/JacobLinCool/Cimple-Lib
 */
#ifndef __CIMPLE_UTILS_STR_H
#define __CIMPLE_UTILS_STR_H

#ifdef DEBUG
#define CHECK_NULL(ptr)                                                                            \
    ({                                                                                             \
        if (ptr == NULL) {                                                                         \
            fprintf(stderr, "Error: %s:%s: %s is NULL.\n", __FILE__, __func__, #ptr);              \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    })
#else
#define CHECK_NULL(ptr) (void)0
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
    char*  data;
    size_t length;
    size_t capacity;
};

struct String* __String_new(const char* data) {
    char* source = (char*)data;
    if (data == NULL) source = "";
    size_t length = strlen(source);

    struct String* string = malloc(sizeof(struct String));
    string->capacity = length + 1;
    string->data = malloc(sizeof(char) * string->capacity);
    strcpy(string->data, data);
    string->length = length;

    return string;
}

struct String* __String_format(const char* format, ...) {
    CHECK_NULL(format);
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);

    struct String* string = malloc(sizeof(struct String));
    string->capacity = length + 1;
    string->data = malloc(sizeof(char) * string->capacity);
    vsprintf(string->data, format, args);
    string->length = length;

    va_end(args);
    return string;
}

struct String* __String_clone(struct String* string) {
    CHECK_NULL(string);
    struct String* clone = malloc(sizeof(struct String));
    clone->capacity = string->capacity;
    clone->data = malloc(sizeof(char) * clone->capacity);
    strcpy(clone->data, string->data);
    clone->length = string->length;

    return clone;
}

struct String* __String_concat(struct String* front, const struct String* back) {
    CHECK_NULL(front);
    CHECK_NULL(back);
    struct String* string = malloc(sizeof(struct String));
    string->capacity = front->length + back->length + 1;
    string->data = malloc(sizeof(char) * string->capacity);
    strcpy(string->data, front->data);
    strcpy(string->data + front->length, back->data);
    string->length = front->length + back->length;

    return string;
}

struct String* __String_trim(struct String* string, const char* charset) {
    CHECK_NULL(string);
    char* chars = (char*)charset;
    if (chars == NULL) chars = " \t\n\r\f\v";

    size_t start = strspn(string->data, chars);
    size_t end = string->length;
    while (end > start && strchr(chars, string->data[end - 1])) end--;

    struct String* trimmed = malloc(sizeof(struct String));
    trimmed->capacity = end - start + 1;
    trimmed->data = malloc(sizeof(char) * trimmed->capacity);
    strncpy(trimmed->data, string->data + start, end - start);
    trimmed->data[end - start] = '\0';
    trimmed->length = end - start;

    return trimmed;
}

struct String* __String_substring(struct String* string, size_t start, size_t end) {
    CHECK_NULL(string);
    if (start > string->length) start = string->length;
    if (end > string->length) end = string->length;
    if (start < 0) start = 0;
    if (end < 0) end = 0;
    if (start > end) {
        size_t temp = start;
        start = end;
        end = temp;
    }

    struct String* substring = malloc(sizeof(struct String));
    substring->capacity = end - start + 1;
    substring->data = malloc(sizeof(char) * substring->capacity);
    strncpy(substring->data, string->data + start, end - start);
    substring->data[end - start] = '\0';
    substring->length = end - start;

    return substring;
}

size_t* __String_search(struct String* string, const char* pattern, size_t* match_size) {
    CHECK_NULL(string);
    CHECK_NULL(pattern);
    size_t* positions = malloc(sizeof(size_t) * string->length);
    size_t  count = 0;
    size_t  pattern_length = strlen(pattern);

    for (size_t i = 0; i < string->length; i++) {
        if (strncmp(string->data + i, pattern, pattern_length) == 0) {
            positions[count++] = i;
            i += pattern_length - 1;
        }
    }

    positions = realloc(positions, sizeof(size_t) * count);
    if (match_size != NULL) *match_size = count;
    return positions;
}

struct String* __String_repeat(struct String* string, size_t times, const char* separator) {
    CHECK_NULL(string);
    char* separator_ = (char*)separator;
    if (separator_ == NULL) separator_ = "";
    size_t length = string->length * times + strlen(separator_) * (times - 1);

    struct String* repeated = malloc(sizeof(struct String));
    repeated->capacity = length + 1;
    repeated->data = malloc(sizeof(char) * repeated->capacity);
    repeated->length = length;

    for (size_t i = 0; i < times; i++) {
        strcpy(repeated->data + i * string->length, string->data);
        strcpy(repeated->data + i * string->length + string->length, separator_);
    }
    repeated->data[length] = '\0';

    return repeated;
}

struct String* __String_replace(struct String* string, const char* old, const char* new) {
    CHECK_NULL(string);
    CHECK_NULL(old);
    CHECK_NULL(new);
    size_t  match_size = 0;
    size_t* matches = __String_search(string, old, &match_size);

    size_t old_length = strlen(old);
    size_t new_length = strlen(new);

    struct String* replaced = malloc(sizeof(struct String));
    replaced->capacity = string->length + (new_length - old_length) * match_size + 1;
    replaced->data = malloc(sizeof(char) * replaced->capacity);
    replaced->length = replaced->capacity - 1;

    strncpy(replaced->data, string->data, match_size ? matches[0] : string->length);
    size_t idx = match_size ? matches[0] : string->length;
    for (size_t i = 0; i < match_size; i++) {
        memcpy(replaced->data + idx, new, new_length);
        idx += new_length;
        memcpy(replaced->data + idx, string->data + matches[i] + old_length,
               i < match_size - 1 ? matches[i + 1] - matches[i] - old_length
                                  : string->length - matches[i] - old_length);
        idx += i < match_size - 1 ? matches[i + 1] - matches[i] - old_length
                                  : string->length - matches[i] - old_length;
    }
    replaced->data[replaced->length] = '\0';

    free(matches);
    return replaced;
}

struct String* __String_upper(struct String* string) {
    CHECK_NULL(string);
    struct String* upper = malloc(sizeof(struct String));
    upper->capacity = string->length + 1;
    upper->data = malloc(sizeof(char) * upper->capacity);
    upper->length = string->length;

    for (size_t i = 0; i < string->length; i++) {
        upper->data[i] = string->data[i] >= 'a' && string->data[i] <= 'z'
                             ? string->data[i] - 'a' + 'A'
                             : string->data[i];
    }
    upper->data[string->length] = '\0';

    return upper;
}

struct String* __String_lower(struct String* string) {
    CHECK_NULL(string);
    struct String* lower = malloc(sizeof(struct String));
    lower->capacity = string->length + 1;
    lower->data = malloc(sizeof(char) * lower->capacity);
    lower->length = string->length;

    for (size_t i = 0; i < string->length; i++) {
        lower->data[i] = string->data[i] >= 'A' && string->data[i] <= 'Z'
                             ? string->data[i] - 'A' + 'a'
                             : string->data[i];
    }
    lower->data[string->length] = '\0';

    return lower;
}

struct String* __String_reverse(struct String* string) {
    CHECK_NULL(string);
    struct String* reversed = malloc(sizeof(struct String));
    reversed->capacity = string->length + 1;
    reversed->data = malloc(sizeof(char) * reversed->capacity);
    reversed->length = string->length;

    for (size_t i = 0; i < string->length; i++) {
        reversed->data[i] = string->data[string->length - i - 1];
    }
    reversed->data[string->length] = '\0';

    return reversed;
}

struct String* __String_pad(struct String* string, size_t length, const char* padding) {
    CHECK_NULL(string);
    if (length <= string->length) return __String_clone(string);

    char* pad = (char*)padding;
    if (pad == NULL) pad = " ";
    size_t pad_length = strlen(pad);

    struct String* padded = malloc(sizeof(struct String));
    padded->capacity = length + 1;
    padded->data = malloc(sizeof(char) * padded->capacity);
    padded->length = length;

    strncpy(padded->data + (length - string->length), string->data, string->length);
    for (size_t i = 0; i < length - string->length; i += pad_length) {
        strncpy(padded->data + i * pad_length, pad,
                i + pad_length > length ? length - i : pad_length);
    }
    padded->data[length] = '\0';

    return padded;
}

struct String** __String_split(struct String* string, const char* separator, size_t* count) {
    CHECK_NULL(string);
    char* sep = (char*)separator;
    if (sep == NULL) sep = " ";
    size_t sep_length = strlen(sep);

    size_t          size = 0;
    struct String** slices = malloc(sizeof(struct String*) * string->length);

    size_t start_idx = 0;
    for (size_t i = 0; i < string->length; i++) {
        if (strncmp(string->data + i, sep, sep_length) == 0) {
            slices[size++] = __String_substring(string, start_idx, i);
            i += sep_length - 1;
            start_idx = i + 1;
        }
    }
    slices[size++] = __String_substring(string, start_idx, string->length);

    slices = realloc(slices, sizeof(struct String*) * size);
    if (count != NULL) *count = size;
    return slices;
}

void __String_free(struct String* string) {
    CHECK_NULL(string);
    free(string->data);
    free(string);
}

void __String_resize(struct String* string, size_t length) {
    CHECK_NULL(string);
    if (length > string->capacity) {
        string->capacity = length + 1;
        string->data = realloc(string->data, sizeof(char) * string->capacity);
    } else if (length < string->length) {
        string->length = length;
        string->data[length] = '\0';
    }
}

void __String_append(struct String* string, const char* data) {
    CHECK_NULL(string);
    CHECK_NULL(data);
    size_t data_length = strlen(data);
    __String_resize(string, string->length + data_length);
    strcpy(string->data + string->length, data);
    string->length += data_length;
}

void __String_prepend(struct String* string, const char* data) {
    CHECK_NULL(string);
    CHECK_NULL(data);
    size_t data_length = strlen(data);
    __String_resize(string, string->length + data_length);
    strcpy(string->data + data_length, string->data);
    memcpy(string->data, data, data_length);
    string->length += data_length;
}

void __String_insert(struct String* string, size_t index, const char* data) {
    CHECK_NULL(string);
    CHECK_NULL(data);
    size_t data_length = strlen(data);
    __String_resize(string, string->length + data_length);
    strcpy(string->data + index + data_length, string->data + index);
    memcpy(string->data + index, data, data_length);
    string->length += data_length;
}

void __String_remove(struct String* string, size_t index, size_t length) {
    CHECK_NULL(string);
    if (index + length >= string->length) {
        string->length = index;
        string->data[index] = '\0';
        return;
    }
    strcpy(string->data + index, string->data + index + length);
    string->length -= length;
}

void __String_clear(struct String* string) {
    CHECK_NULL(string);
    string->length = 0;
    string->data[0] = '\0';
}

struct {
    /**
     * Construct a new String from a C string.
     * If NULL is passed, a new empty String is created.
     */
    struct String* (*new)(const char*);
    /**
     * Construct a new String from a C string with IO formatting.
     */
    struct String* (*format)(const char* format, ...);
    /**
     * Clone a String.
     */
    struct String* (*clone)(struct String* string);
    /**
     * Concats two Strings and returns the new String.
     */
    struct String* (*concat)(struct String* front, const struct String* back);
    /**
     * Trim the chars from the beginning and end of a String and returns the new String.
     * If charset is NULL, the default charset ( \\t\\n\\r\\f\\v ) is used.
     */
    struct String* (*trim)(struct String* string, const char* charset);
    /**
     * Extract a substring from a String and returns the new String.
     */
    struct String* (*substring)(struct String* string, size_t start, size_t end);
    /**
     * Search for a substring in a String and returns the index of occurrences, with size `count`.
     */
    size_t* (*search)(struct String* string, const char* pattern, size_t* count);
    /**
     * Repeat a String with separator for a given number of times and returns the new String.
     */
    struct String* (*repeat)(struct String* string, size_t times, const char* separator);
    /**
     * Replace a substring in a String with another substring and returns the new String.
     */
    struct String* (*replace)(struct String* string, const char* old, const char* new);
    /**
     * Make a String uppercase and returns the new String.
     */
    struct String* (*upper)(struct String* string);
    /**
     * Make a String lowercase and returns the new String.
     */
    struct String* (*lower)(struct String* string);
    /**
     * Reverse a String and returns the new String.
     */
    struct String* (*reverse)(struct String* string);
    /**
     * Pad a String with a given string and returns the new String.
     */
    struct String* (*pad)(struct String* string, size_t length, const char* pad);
    /**
     * Split a String with a given separator and returns the new String array.
     */
    struct String** (*split)(struct String* string, const char* delimiter, size_t* count);
    /**
     * Free a String.
     */
    void (*free)(struct String* string);
    /**
     * Resize a String to a given length.
     */
    void (*resize)(struct String* string, size_t length);
    /**
     * Append a C string to a String.
     */
    void (*append)(struct String* string, const char* data);
    /**
     * Prepend a C string to a String.
     */
    void (*prepend)(struct String* string, const char* data);
    /**
     * Insert a C string at a given index in a String.
     */
    void (*insert)(struct String* string, size_t index, const char* data);
    /**
     * Remove a range of index and length in a String.
     */
    void (*remove)(struct String* string, size_t index, size_t length);
    /**
     * Clear a String.
     */
    void (*clear)(struct String* string);
} String = {.new = __String_new,
            .format = __String_format,
            .clone = __String_clone,
            .concat = __String_concat,
            .trim = __String_trim,
            .substring = __String_substring,
            .search = __String_search,
            .repeat = __String_repeat,
            .replace = __String_replace,
            .upper = __String_upper,
            .lower = __String_lower,
            .reverse = __String_reverse,
            .pad = __String_pad,
            .split = __String_split,
            .free = __String_free,
            .resize = __String_resize,
            .append = __String_append,
            .prepend = __String_prepend,
            .insert = __String_insert,
            .remove = __String_remove,
            .clear = __String_clear};

#endif  // __CIMPLE_UTILS_STR_H
