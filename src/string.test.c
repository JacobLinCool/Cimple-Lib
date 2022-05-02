#include "string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_string_utils();

int main() {
    test_string_utils();
    return EXIT_SUCCESS;
}

void test_string_utils() {
    char* my_string = strdup("   hello world     \n\n\t");

    char* trimmed = String.trim(my_string, NULL);
    assert(strlen(trimmed) == 11);
    assert(strcmp(trimmed, "hello world") == 0);
    free(trimmed);

    trimmed = String.trim(my_string, " \thelo");
    assert(strlen(trimmed) == 12);
    assert(strcmp(trimmed, "world     \n\n") == 0);
    free(trimmed);
    free(my_string);

    my_string = strdup("Hello world!!!");
    char* replaced = String.replace(my_string, "!", "?");
    assert(strlen(replaced) == 14);
    assert(strcmp(replaced, "Hello world???") == 0);
    free(replaced);
    free(my_string);

    my_string = strdup("There is a cat in the house");
    size_t size;
    char** slices = String.split(my_string, " ", &size);
    assert(size == 7);
    assert(strcmp(slices[0], "There") == 0);
    assert(strcmp(slices[1], "is") == 0);
    assert(strcmp(slices[2], "a") == 0);
    assert(strcmp(slices[3], "cat") == 0);
    assert(strcmp(slices[4], "in") == 0);
    assert(strcmp(slices[5], "the") == 0);
    assert(strcmp(slices[6], "house") == 0);
    for (int i = 0; i < size; i++) {
        free(slices[i]);
    }
    free(slices);
    free(my_string);

    my_string = strdup("Hello!");
    slices = String.split(my_string, NULL, &size);
    assert(size == 1);
    assert(strcmp(slices[0], "Hello!") == 0);
    for (int i = 0; i < size; i++) {
        free(slices[i]);
    }
    free(slices);
    free(my_string);
}
