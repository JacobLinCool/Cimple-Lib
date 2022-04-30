#include "string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String* Str;

void test_String_create();
void test_String_manipulate();
void test_String_advanced();

int main() {
    test_String_create();
    test_String_manipulate();
    test_String_advanced();
    return EXIT_SUCCESS;
}

void test_String_manipulate() {
    Str my_string = String.new("hello world!");
    assert(my_string->length == 12);
    assert(strcmp(my_string->data, "hello world!") == 0);

    String.clear(my_string);
    assert(my_string->length == 0);
    assert(strcmp(my_string->data, "") == 0);

    String.append(my_string, "!!!");
    assert(my_string->length == 3);
    assert(strcmp(my_string->data, "!!!") == 0);

    String.prepend(my_string, "Hello ");
    assert(my_string->length == 9);
    assert(strcmp(my_string->data, "Hello !!!") == 0);

    String.insert(my_string, 6, "world");
    assert(my_string->length == 14);
    assert(strcmp(my_string->data, "Hello world!!!") == 0);

    String.remove(my_string, 5, 6);
    assert(my_string->length == 8);
    assert(strcmp(my_string->data, "Hello!!!") == 0);

    String.remove(my_string, 0, 100000);
    assert(my_string->length == 0);
    assert(strcmp(my_string->data, "") == 0);

    String.free(my_string);
}

void test_String_create() {
    Str my_string = String.new("hello world!");
    assert(my_string->length == 12);
    assert(strcmp(my_string->data, "hello world!") == 0);
    String.free(my_string);

    my_string = String.format("%s %s! %d", "hello", "world", 42);
    assert(my_string->length == 15);
    assert(strcmp(my_string->data, "hello world! 42") == 0);
    String.free(my_string);
}

void test_String_advanced() {
    Str my_string = String.new("   hello world     \n\n\t");

    Str trimmed = String.trim(my_string, NULL);
    assert(trimmed->length == 11);
    assert(strcmp(trimmed->data, "hello world") == 0);
    String.free(trimmed);

    trimmed = String.trim(my_string, " \thelo");
    assert(trimmed->length == 12);
    assert(strcmp(trimmed->data, "world     \n\n") == 0);
    String.free(trimmed);
    String.free(my_string);

    my_string = String.new("Hello world!!!");
    Str replaced = String.replace(my_string, "!", "?");
    assert(replaced->length == 14);
    assert(strcmp(replaced->data, "Hello world???") == 0);
    String.free(replaced);
    String.free(my_string);

    my_string = String.new("There is a cat in the house");
    size_t size;
    Str*   slices = String.split(my_string, " ", &size);
    assert(size == 7);
    assert(strcmp(slices[0]->data, "There") == 0);
    assert(strcmp(slices[1]->data, "is") == 0);
    assert(strcmp(slices[2]->data, "a") == 0);
    assert(strcmp(slices[3]->data, "cat") == 0);
    assert(strcmp(slices[4]->data, "in") == 0);
    assert(strcmp(slices[5]->data, "the") == 0);
    assert(strcmp(slices[6]->data, "house") == 0);
    for (int i = 0; i < size; i++) {
        String.free(slices[i]);
    }
    free(slices);
    String.free(my_string);

    my_string = String.new("Hello!");
    slices = String.split(my_string, NULL, &size);
    assert(size == 1);
    assert(strcmp(slices[0]->data, "Hello!") == 0);
    for (int i = 0; i < size; i++) {
        String.free(slices[i]);
    }
    free(slices);
    String.free(my_string);
}
