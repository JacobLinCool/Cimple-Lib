// #define DEBUG
#include "../lib/base.h"
#include "../lib/debug.h"

i32 main() {
    DBG(
        printf(CLR_MAGENTA "-- Debugging... --\n" CLR_NONE);
    );

    THROW("%s\n", "This is a test.");
    THROW_IF(1 != 1, "%s\n", "1 != 1");
    THROW_IF(1 == 1, "%s\n", "1 == 1");

    return 0;
}
