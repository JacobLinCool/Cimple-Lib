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

`String` utilities.

```c
struct {
    /**
     * Construct a new string with IO formatting.
     */
    char* (*format)(const char* format, ...);
    /**
     * Trim the chars from the beginning and end of a string and returns the new string.
     * If charset is NULL, the default charset ( \\t\\n\\r\\f\\v ) is used.
     */
    char* (*trim)(const char* string, const char* charset);
    /**
     * Extract a substring from a string and returns the new string.
     */
    char* (*substring)(const char* string, size_t start, size_t end);
    /**
     * Search for a substring in a string and returns the index of occurrences, with size `count`.
     */
    size_t* (*search)(const char* string, const char* pattern, size_t* count);
    /**
     * Repeat a string with separator for a given number of times and returns the new string.
     */
    char* (*repeat)(const char* string, size_t times, const char* separator);
    /**
     * Replace a substring in a string with another substring and returns the new string.
     */
    char* (*replace)(const char* string, const char* old, const char* new);
    /**
     * Make a string uppercase and returns the new string.
     */
    char* (*upper)(const char* string);
    /**
     * Make a string lowercase and returns the new string.
     */
    char* (*lower)(const char* string);
    /**
     * Reverse a string and returns the new string.
     */
    char* (*reverse)(const char* string);
    /**
     * Pad a string with a given string and returns the new string.
     */
    char* (*pad)(const char* string, size_t length, const char* pad);
    /**
     * Split a string with a given separator and returns the new string array.
     */
    char** (*split)(const char* string, const char* delimiter, size_t* count);
} String;
```

**Example**

```c
char* my_string = String.format("There are %d monkeys in the %s", 10, "tree");

size_t size;
char** words = String.split(my_string, " ", &size);
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

### `bucket.h`

Pointer manager. It can help you to elegantly code with function chaining.

`$()`, `$clear()`, ...

**Example**

```c
for (int i = 0; i < 4096; i++) {
    char* str = $(calloc(1024, sizeof(char)));
    sprintf(str, "%d", i);
}

assert($size() == 4096);
assert($capacity() == 4096);
$free(); // free all pointers at once
```

```c
// With $
char* str = String.upper($(String.trim($(String.format("%s %s!", "  Hello", "World")), " ")));
$free(); // free the intermediates
assert(strcmp(str, "HELLO WORLD!") == 0);
do_something(str);

// Without $
char* formatted = String.format("%s %s!", "  Hello", "World");
char* trimmed = String.trim(formatted, " ");
free(formatted);
char* str = String.upper(trimmed);
free(trimmed);
assert(strcmp(str, "HELLO WORLD!") == 0);
do_something(str);
```

## Run Tests

1. Clone the repository and cd into the directory.
2. Run `make` to compile the C code.

Or just open in Gitpod:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/JacobLinCool/Cimple-Lib)

## Some Concepts

### Why using `String.lower` instead of `strlower`?

Namespace is a good idea, although it is not exisiting in C, but we can still simulate it by using a global struct.

Benefits:

- Avoid naming conflicts (pollution)
- Provide library description through VS Code intellisense

The only downside is that dereferring a function pointer may have a small cost. (Maybe compiler will optimize it away?)
