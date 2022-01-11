// Copyright (c) JacobLinCool
#include "helper.h"
#define DEBUG 1

i64 climb_stairs(i64 n) {
    if (n <= 2) {
        return n;
    }

    i64 prev_1 = 2, prev_2 = 1, now = 0;

    for (i64 i = 3; i <= n; i++) {
        now = prev_1 + prev_2;
        prev_2 = prev_1;
        prev_1 = now;
    }

    return now;
}

int main() {
    for (i64 i = 0; i <= 11; i++) {
        struct timespec start_time = TIME_START();
        i64 stairs = (i64)pow(2, i);
        printf("Climbing %" PRId64 " Stairs: %" PRId64 "\n", stairs, climb_stairs(stairs));
        DEBUG_PRINT("Calculation spent %lg ms\n\n", TIME_CHECK(start_time));
    }

    return 0;
}

// Any application that can be written in JavaScript, will eventually be written in JavaScript.
