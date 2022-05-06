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

### `buffer.h`

Bit operations and endianness conversion.

```c
/**
 * @brief Buffer utility functions.
 */
struct {
    /**
     * @brief Get bit from buffer
     * @param buffer The buffer
     * @param bit The bit to be get
     */
    bool (*get_bit)(const void* buffer, size_t bit);
    /**
     * @brief Set bit in buffer
     * @param buffer The buffer
     * @param bit The bit to be set
     * @param value The value to be set
     */
    void (*set_bit)(void* buffer, size_t bit, bool value);
    /**
     * @brief Stringify the buffer
     * @param buffer The buffer
     * @param size The size of the buffer, in bits
     * @param col_size The size of each column, in bits
     * @param row_size The size of each row, in columns
     */
    char* (*stringify)(const void* buffer, size_t size, size_t col_size, size_t row_size);
    /**
     * @brief Parse a stringified buffer into a buffer
     * @param buffer The buffer
     * @param str The string to be parsed
     * @param size The size of the buffer, in bits
     */
    void (*parse)(void* buffer, const char* str, size_t size);
    /**
     * @brief Get the endian of the system
     * @return true if the system is little endian, false otherwise
     */
    bool (*endian)();
    /**
     * @brief Reverse the buffer
     * @param buffer The buffer
     * @param size The size of the buffer, in bytes
     */
    uint8_t* (*reverse)(const void* buffer, size_t size);
    /**
     * @brief Convert a little endian buffer to big endian
     * @param buffer The buffer
     * @param size The size of the buffer, in bits
     */
    void* (*to_big)(const void* buffer, size_t size);
    /**
     * @brief Convert a big endian buffer to little endian
     * @param buffer The buffer
     * @param size The size of the buffer, in bits
     */
    void* (*to_little)(const void* buffer, size_t size);
} Buffer;
```

**Example**

```c
uint8_t* buffer = calloc(16 / 8, sizeof(uint8_t));
for (int i = 0; i < 16; i++) {
    Buffer.set_bit(buffer, i, i % 2);
}
for (int i = 0; i < 16; i++) {
    assert(Buffer.get_bit(buffer, i) == i % 2);
}

char* str = Buffer.stringify(buffer, 16, 8, 8);
printf("%s\n", str); // "01010101 01010101"
```

### `options.h`

Parse command line options.

```c
struct {
    /**
     * @brief Parse command line arguments
     * @param argc number of arguments
     * @param argv array of arguments
     * @return parsed options
     */
    ParsedOptions* (*parse)(size_t argc, char* argv[]);
    /**
     * @brief Get an option from the parsed options
     * @param options parsed options
     * @param name name of the option
     * @return value of the option
     */
    char* (*get)(ParsedOptions* options, char* name);
    /**
     * @brief Check if an option is present
     * @param options parsed options
     * @param name name of the option
     * @return true if the option is present, false otherwise
     */
    bool (*has)(ParsedOptions* options, char* name);
    /**
     * @brief Free the parsed options
     * @param options parsed options
     */
    void (*free)(ParsedOptions* options);
} Options;
```

**Example**

```c
ParsedOptions* options = Options.parse(argc, argv);

if (Options.has(options, "help") || Options.has(options, "h")) {
    printf("Usage: %s --name <something>\n", argv[0]);
    return 0;
}

printf("Hello, %s!\n", Options.get(options, "name") || "XYZ");
Options.free(options);
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
