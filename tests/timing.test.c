#include "../lib/base.h"
#include "../lib/timing.h"

i32 main() {
    timing_start("test");
    sleep(100);
    assert(timing_check("test") > 90.0 && timing_check("test") < 110.0);

    printf(">> [Timing] All tests passed! <<\n");

    return 0;
}
