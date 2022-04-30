# Cimple Lib

A delightful helper library for C learners.

Good for someone who needs to do C programming homework.

<!-- It helps me to learn how to use (fancy) macros in C. -->

## Usage

All libraries are _header files_, so you can directly include them in your C code.

Since the libraries are all lightweight, we don't have to worry about the compilation time.

```c
#include "src/all.h"

int main() {
    char* label = "print 1 to 1000";
    Timing.start(label);
    for (int i = 1; i <= 1000; i++) {
        Console.rainbow("%d", i);
    }
    Console.log("%s: %Lf ms", label, Timing.check(label));

    return 0;
}
```

I recommend you to use VS Code because of the great language server support.

![language server](img/language-server.png)

## Features

### `all.h`

Includes all the libraries below.

### `base.h`

This header file includes:

- Standard libraries that are useful in most cases.
- Type alias for standard types.
  - `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`, `f32`, `f64`, `f128`

### `console.h`

`Console` utilities.

```c
struct {
    size_t (*gray)(const char* str, ...);
    size_t (*red)(const char* str, ...);
    size_t (*green)(const char* str, ...);
    size_t (*blue)(const char* str, ...);
    size_t (*yellow)(const char* str, ...);
    size_t (*magenta)(const char* str, ...);
    size_t (*cyan)(const char* str, ...);

    size_t (*success)(const char* str, ...);
    size_t (*info)(const char* str, ...);
    size_t (*warn)(const char* str, ...);
    size_t (*error)(const char* str, ...);

    /** Logs a message to the console, with time prefix */
    void (*log)(const char* str, ...);

    /** Print in rainbow colors */
    size_t (*rainbow)(const char* str, ...);

    /** Color constants */
    struct {
        const char* GRAY;
        const char* RED;
        const char* GREEN;
        const char* BLUE;
        const char* YELLOW;
        const char* MAGENTA;
        const char* CYAN;
    } C;
} Console;
```

### `string.h`

`struct String` and `String` utilities.

```c
struct String {
    char*  data;
    size_t length;
    size_t capacity;
};

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
} String;
```

**Example**

```c
typedef struct String* Str;

Str my_string = String.format("There are %d monkeys in the %s", 10, "tree");

size_t size;
Str* words = String.split(my_string, " ", &size);
```

### `debug.h`

Debug utilities.

`THROW` `THROW_IF`

### `timing.h`

`Timing` utilities.

```c
struct {
    /**
     * @brief Start a timer with a label.
     * @param label The label of the timer.
     */
    bool (*start)(const char* label);
    /**
     * @brief Get the time elapsed since the last timing_start() call.
     * @param label The label of the timer.
     * @return long double The time elapsed since the last timing_start() call in milliseconds.
     */
    long double (*check)(const char* label);
    /**
     * @brief Remove a timer with a label.
     * @param label The label of the timer.
     * @return bool True if the timer is removed successfully.
     */
    bool (*remove)(const char* label);
    /**
     * @brief Clear all the timers.
     * @return size_t The number of timers cleared.
     */
    size_t (*clear)();
    /**
     * @brief Sleep for a certain amount of milliseconds.
     * @param ms The amount of milliseconds to sleep.
     */
    void (*sleep)(const uint64_t ms);
} Timing;
```

**Example**

```c
Timing.start("test");
Timing.sleep(500);
Console.cyan("%Lf ms", Timing.check("test"));
Timing.sleep(500);
Console.yellow("%Lf ms", Timing.check("test"));
```

## Run Tests

1. Clone the repository and cd into the directory.
2. Run `make` to compile the C code.

Or just open in Gitpod:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/JacobLinCool/Cimple-Lib)
