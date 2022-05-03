#include "buffer.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    uint8_t* buffer = calloc(1024 / 8, sizeof(uint8_t));
    assert(buffer != NULL);

    for (int i = 0; i < 1024; i++) {
        Buffer.set_bit(buffer, i, i % 2);
    }

    for (int i = 0; i < 1024; i++) {
        assert(Buffer.get_bit(buffer, i) == i % 2);
    }

    char* str = Buffer.stringify(buffer, 1024, 8, 8);
    // printf("%s\n", str);

    Buffer.parse(buffer, str, 1024);
    char* str2 = Buffer.stringify(buffer, 1024, 8, 8);
    assert(strcmp(str, str2) == 0);
    free(str);
    free(str2);
    // printf("%s\n", str2);

    free(buffer);

    uint32_t* reversed = Buffer.reverse(&(uint32_t){0x01020304}, 4);
    assert(*reversed == 0x04030201);
    free(reversed);

    size_t   size = 13;
    uint16_t val = 1234;
    // printf("%s\n", Buffer.stringify(&val, size, 8, 8));
    void* big = Buffer.to_big(&val, size);
    // printf("%s\n", Buffer.stringify(big, size, -1, 8));
    uint16_t* val_2 = Buffer.to_little(big, size);
    // printf("%s\n", Buffer.stringify(&val_2, size, 8, 8));
    assert(val == *val_2);
    free(big);
    free(val_2);

    return EXIT_SUCCESS;
}
