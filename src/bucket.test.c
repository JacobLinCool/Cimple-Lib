#include "bucket.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    for (int i = 0; i < 4096; i++) {
        char* str = $(calloc(1024, sizeof(char)));
        assert(str != NULL);
        sprintf(str, "%d", i);
    }
    assert($size() == 4096);
    assert($capacity() == 4096);
    $free();
    assert($size() == 0);
    assert($capacity() == 4096);

    return EXIT_SUCCESS;
}
