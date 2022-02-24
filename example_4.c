// Copyright (c) JacobLinCool
// #define DEBUG 1
#include "helper.h"

int main() {
    i64 input = 0;
    printf("Please input a number: ");
    scanf("%" SCNd64, &input);

    THROW_IF(input < 0, "Input must be positive. Recieved: %" PRId64 "\n", input);
    THROW_IF(input > 100, "Input must be less than 100. Recieved: %" PRId64 "\n", input);

    printf("%" PRId64 " is %s\n", input, input % 2 == 0 ? "Even" : "Odd");

    return 0;
}

// Any application that can be written in JavaScript, will eventually be written in JavaScript.
