#include "console.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_Console_constants();

int main() {
    test_Console_constants();
    return EXIT_SUCCESS;
}

void test_Console_constants() {
    assert(strcmp(Console.C.GRAY, __FMT_GRAY) == 0);
    assert(strcmp(Console.C.RED, __FMT_RED) == 0);
    assert(strcmp(Console.C.GREEN, __FMT_GREEN) == 0);
    assert(strcmp(Console.C.BLUE, __FMT_BLUE) == 0);
    assert(strcmp(Console.C.YELLOW, __FMT_YELLOW) == 0);
    assert(strcmp(Console.C.MAGENTA, __FMT_MAGENTA) == 0);
    assert(strcmp(Console.C.CYAN, __FMT_CYAN) == 0);
}
