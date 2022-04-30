#include "timing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Timing.start("test");
    Timing.sleep(100);
    long double elapsed = Timing.check("test");
    assert(elapsed >= 100.0);

    return EXIT_SUCCESS;
}
