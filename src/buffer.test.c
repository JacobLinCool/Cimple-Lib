#include "buffer.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timing.h"

int main() {
    uint8_t* buffer = calloc(1024 / 8, sizeof(uint8_t));
    assert(buffer != NULL);

    Timing.start("set");
    for (int i = 0; i < 1024; i++) {
        Buffer.set_bit(buffer, i, i % 2);
    }
    // printf("Set: %Lf\n", Timing.check("set"));

    Timing.start("get");
    for (int i = 0; i < 1024; i++) {
        assert(Buffer.get_bit(buffer, i) == i % 2);
    }
    // printf("Get: %Lf\n", Timing.check("get"));

    Timing.start("stringify");
    char* str = Buffer.stringify(buffer, 1024, 8, 8);
    // printf("Stringify: %Lf\n", Timing.check("stringify"));
    // printf("%s\n", str);

    Timing.start("parse");
    Buffer.parse(buffer, str, 1024);
    // printf("Parse: %Lf\n", Timing.check("parse"));
    char* str2 = Buffer.stringify(buffer, 1024, 8, 8);
    // printf("%s\n", str2);

    assert(*(uint32_t*)Buffer.reverse(&(uint32_t){0x01020304}, 4) == 0x04030201);

    size_t   size = 13;
    uint16_t val = 1234;
    // printf("%s\n", Buffer.stringify(&val, size, 8, 8));
    void* big = Buffer.to_big(&val, size);
    // printf("%s\n", Buffer.stringify(big, size, -1, 8));
    uint16_t val_2 = *(uint16_t*)Buffer.to_little(big, size);
    // printf("%s\n", Buffer.stringify(&val_2, size, 8, 8));
    assert(val == val_2);

    return EXIT_SUCCESS;
}
