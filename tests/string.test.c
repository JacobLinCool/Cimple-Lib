#include "../lib/base.h"
#include "../lib/string.h"

void test_trim();
void test_split();
void test_join();
void test_replace();

i32 main() {
    test_trim();
    test_split();
    test_join();
    test_replace();

    printf(">> [String] All tests passed! <<\n");

    return 0;
}

void test_trim() {
    char str[] = "  hello world  \n";

    char* trimmed = TRIM(str);
    assert(strcmp(trimmed, "hello world") == 0);
    free(trimmed);

    trimmed = TRIM(str, TRIM_LEFT);
    assert(strcmp(trimmed, "hello world  \n") == 0);
    free(trimmed);

    trimmed = TRIM(str, TRIM_RIGHT);
    assert(strcmp(trimmed, "  hello world") == 0);
    free(trimmed);

    trimmed = TRIM(str, TRIM_LEFT | TRIM_RIGHT, "hello ");
    assert(strcmp(trimmed, "world  \n") == 0);
    free(trimmed);

    return;
}

void test_split() {
    char str[] = "To be, or not to be, that is the question.";
    u64 count = 0;

    char** slices = SPLIT(str, &count);
    assert(count == 10);
    char* expected1[10] = { "To", "be,", "or", "not", "to", "be,", "that", "is", "the", "question." };
    for (u64 i = 0; i < count; i++) {
        assert(strcmp(slices[i], expected1[i]) == 0);
        free(slices[i]);
    }
    free(slices);

    char* delimiters[2] = { "be", "is" };
    slices = SPLIT(str, &count, delimiters, 2);
    assert(count == 4);
    char* expected2[4] = { "To ", ", or not to ", ", that ", " the question." };
    for (u64 i = 0; i < count; i++) {
        assert(strcmp(slices[i], expected2[i]) == 0);
        free(slices[i]);
    }
    free(slices);

    char empty_str[] = "";
    slices = SPLIT(empty_str, &count);
    assert(count == 1);
    assert(strcmp(slices[0], "") == 0);
    free(slices[0]);
    free(slices);

    count = 0;
    slices = SPLIT(empty_str, &count, (string[]) { "" }, 1);
    assert(count == 1);
    assert(strcmp(slices[0], "") == 0);
    free(slices[0]);
    free(slices);

    return;
}

void test_join() {
    char* slices[3] = { "To", "be,", "or not to be." };
    char* joined = JOIN(slices, sizeof(slices) / sizeof(char*));
    assert(strcmp(joined, "To be, or not to be.") == 0);
    free(joined);

    char* glue = "<->";
    joined = JOIN(slices, sizeof(slices) / sizeof(char*), glue);
    assert(strcmp(joined, "To<->be,<->or not to be.") == 0);
    free(joined);

    return;
}

void test_replace() {
    char str[] = "To be, or not to be, that is the question.";

    char* replaced = replace(str, "be", "eat");
    assert(strcmp(replaced, "To eat, or not to eat, that is the question.") == 0);
    free(replaced);

    return;
}
