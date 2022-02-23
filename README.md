# C Helper

A delightful helper library for C learners.

Good for someone who needs to do C programming homework.

It also helps me to learn how to use macros in C.

## Usage

### Single File

Just copy and paste all code in `helper.c` to the beginning of your C file.

### Better Usage

Download and put the `helper.h` header file in your project's directory.

```c
#include "helper.h"
// You MUST define DEBUG:
#define DEBUG 1 // Enable debug mode, or 0 to disable

int main() {
    printf("Hello, world!\n");
    DEBUG_PRINT("Hello, world!\n");
    return 0;
}
```

See [Makefile](./Makefile) for compiling and linking example.

See [example_1](./example_1.c), [example_2](./example_2.c), and [example_3](./example_3.c) for code examples.

## Run Examples

1. Clone the repository and cd into the directory.
2. Run `make` to compile the C code.
3. `./example_1` to run the first example.
4. `./example_2` to run the second example.
5. `./example_3` to run the third example.

Or just open in Gitpod:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/JacobLinCool/C-Helper)

## Features

- Include Common Header Files
  - `assert.h` - `assert`, for debugging
  - `errno.h` - Error codes
  - `inttypes.h` - `PRId64` and friends
  - `math.h` - Math functions
  - `stdbool.h` - `true` and `false`
  - `stdint.h` - `int64_t` and friends
  - `stdio.h` - `printf`, `scanf` and friends
  - `stdlib.h` - `malloc`, `free` and friends
  - `string.h` - `strlen`, `strcmp` and friends
  - `time.h` - `time` and `clock`
- Type Alias for Standard Types
  - `i8`, `i16`, `i32`, `i64` - Shorthand for `int8_t`, `int16_t`, `int32_t`, `int64_t`
  - `u8`, `u16`, `u32`, `u64` - Shorthand for `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`
  - `f32`, `f64`, `f128` - Shorthand for `float`, `double`, `long double`
- Function Macros for Cross-Type Number Operations
  - `MAX(a, b)` - Returns maximum of `a` and `b`
  - `MIN(a, b)` - Returns minimum of `a` and `b`
  - `ABS(a)` - Returns absolute value of `a`
  - `FLOOR(a)` - Returns floor of `a`
  - `CEIL(a)` - Returns ceiling of `a`
  - `ROUND(a)` - Returns round of `a`
- Function Macros for Array
  - `ARRAY_LENGTH(arr)` - Returns the length of an array
  - `ARRAY_MAX(arr, *idx)` - Returns the maximum value of an array, and its index
  - `ARRAY_MIN(arr, *idx)` - Returns the minimum value of an array, and its index
  - `ARRAY_SUM(arr)` - Returns the sum of all values in an array
  - `ARRAY_AVG(arr)` - Returns the average of all values in an array
- Function Macros for Debugging
  - `DEBUG_PRINT` - like `printf`, but only prints when `DEBUG` is `1`
  - `DEBUG_PRINT_ARRAY` - Print an array easily
  - `DEBUG_PRINT_MEMORY` - Print the memory layout around a pointer
- Function Macros for Execution Time Measurement
  - `TIME_START()` - Returns a `struct timespec` representing the start time
  - `TIME_CHECK(start)` - Returns the time elapsed since `start`, in milliseconds
