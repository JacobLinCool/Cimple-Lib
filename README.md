# C Helper

A delightful helper library for C learners.

Good for someone who needs to do C programming homework.

It helps me to learn how to use (fancy) macros in C.

## Usage

There are a lot of header files in `lib` directory.

You can pick some of them you want to use and include them in your file.

Careful! Some header files need to work with other header files. 
For example, almost every header file in `lib` directory needs to include `base.h` header file.

*The `helper.h` includes all header files in `lib` directory.*

```c
#define DEBUG // Enable debug mode, Remove this line or comment it out to disable debug mode
#include "helper.h"

int main() {
    printf("Hello, world!\n");
    DBG_PRINT("Hello, world!\n");
    return 0;
}
```

See [Makefile](./Makefile) for compiling example, actually you do not need to worry about that.

See tests in `tests` directory to see how to use this library in action.

## Run Examples (Tests)

1. Clone the repository and cd into the directory.
2. Run `make` to compile the C code.

Or just open in Gitpod:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/JacobLinCool/C-Helper)

## Features

### `base.h`

This header file includes:

- Standard libraries that are useful in most cases.
- Type alias for standard types.

*This header file only has macros.*

#### libraries included

```c
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
```

#### type alias

- `i8`, `i16`, `i32`, `i64`
  - `int8_t`, `int16_t`, `int32_t`, `int64_t`
- `u8`, `u16`, `u32`, `u64`
  - `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`
- `f32`, `f64`, `f128`
  - `float`, `double`, `long double`
- `string`
  - `char*`

#### ansi colors

```c
#define CLR_RED     "\x1b[91m"
#define CLR_GREEN   "\x1b[92m"
#define CLR_YELLOW  "\x1b[93m"
#define CLR_BLUE    "\x1b[94m"
#define CLR_MAGENTA "\x1b[95m"
#define CLR_CYAN    "\x1b[96m"
#define CLR_NONE    "\x1b[0m"
```

### `string.h`

String utilities with DEFAULT VALUE support and OVERLOADING support.

#### `trim` & `TRIM`

`trim` can trim the leading and/or trailing characters.

```c
 /**
  * @brief Trim the string.
  *
  * @param target The string to be trimmed.
  * @param mode The trim mode. 3: both side, 1: left side, 2: right side.
  * @param dict The trim dictionary.
  * @return string The trimmed string.
  */
string trim(string target, u8 mode, string dict);
```

`TRIM` is just like `trim`, but it supports DEFAULT VALUE.

You can see it like this:

```c
TRIM(string target, u8 mode = 3, string dict = "\t\n\r ");
```

#### `split` & `SPLIT`

`split` can split the string by the given delimiter(s).

```c
/**
 * @brief Split the string into slices by the given delimiter strings.
 *
 * @param target The string to be splitted.
 * @param count The number of slices. This is a return value.
 * @param delimiters The delimiter strings.
 * @param delimiter_count The number of delimiter strings.
 * @return string* The slices.
 */
string* split(string target, u64* count, string* delimiters, u64 delimiter_count);
```

`SPLIT` is just like `split`, but it supports OVERLOADING.

```c
SPLIT(string target, u64* count); // delimiters = (string[]){" "}, delimiter_count = 1
SPLIT(string target, u64* count, string* delimiters, u64 delimiter_count);
```

#### `join` & `JOIN`

`join` can join the slices into a string.

```c
/**
 * @brief Join the slices into a string.
 *
 * @param slices The slices.
 * @param count The number of slices.
 * @param glue The glue string.
 * @return string The joined string.
 */
string join(string* slices, u64 count, string glue);
```

`JOIN` is just like `join`, but it supports OVERLOADING.

```c
JOIN(string* slices, u64 count); // glue = " "
JOIN(string* slices, u64 count, string glue);
```

#### `replace`

`replace` can replace "keyword"s in "target" with "replacement".

```c
/**
 * @brief Replace the string with the given keyword and replacement.
 *
 * @param target The string to be replaced.
 * @param keyword The keyword to be replaced.
 * @param replacement The replacement.
 * @return string The replaced string.
 */
string replace(string target, string keyword, string replacement);
```

I don't think we need any default value or overloading for `replace`.

### `array.h`

`array_map` and `array_reduce`.

### `format.h`

#### `tint`

```c
 /**
  * @brief Tint the string.
  *
  * @param str The string to be tinted.
  * @param color The color of the string.
  * @return string The tinted string.
  */
string tint(string str, string color);
```

#### `format_array`

```c
format_array(type, array, from, to)
```

`type` can be `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`, `f32`, `f64`, `f128`, `cahr`, `str`, or `ptr`.

Example:

```c
string a[] = { "Hello", "World", "12345" };
string str = format_array(str, a, 0, 2);
printf("%s\n", str);
```

### `debug.h`

Debug utilities.

### `timing.h`

Time measurement utilities.
