#include "file.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_File();

int main() {
    test_File();
    return EXIT_SUCCESS;
}

void test_File() {
    File.write("test.txt", (uint8_t*)"Hello World!\n", 13);
    char* content = (char*)File.read("test.txt");
    assert(strcmp(content, "Hello World!\n") == 0);
    free(content);

    File.append("test.txt", (uint8_t*)"Hello World!\n", 13);
    content = (char*)File.read("test.txt");
    assert(strcmp(content, "Hello World!\nHello World!\n") == 0);
    free(content);

    assert(File.remove("test.txt") == true);
}
