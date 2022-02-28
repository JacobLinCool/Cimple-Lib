#include "../lib/base.h"
#include "../lib/array.h"
#define x7(x) x * 7

char* strcat_alloc(const char* str1, const char* str2) {
    char* str = (char*)malloc((strlen(str1) + strlen(str2) + 1) * sizeof(char));
    strcpy(str, str1);
    strcat(str, str2);
    return str;
}

u64 sum(u64 acc, u64 x, u64 i) {
    return acc + x;
}

void test_array_map();
void test_array_reduce();

i32 main() {
    test_array_map();
    test_array_reduce();

    printf(">> [Array] All tests passed! <<\n");

    return 0;
}

void test_array_map() {
    u64 arr1[] = { 1, 2, 3, 4, 5 };
    f64 arr2[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    char* arr3[] = { "Hello", "World", "!" };

    u64* result1 = array_map(arr1, 5, u64, x7);
    for (u64 i = 0; i < 5; i++) {
        assert(result1[i] == arr1[i] * 7);
    }
    free(result1);

    f64* result2 = array_map(arr2, 5, f64, x7);
    for (u64 i = 0; i < 5; i++) {
        assert(result2[i] == arr2[i] * 7);
    }
    free(result2);

    f64* result3 = array_map(arr2, 5, f64, sqrt);
    for (u64 i = 0; i < 5; i++) {
        assert(result3[i] == sqrt(arr2[i]));
    }
    free(result3);

    u64* result4 = array_map(arr3, 3, u64, strlen);
    for (u64 i = 0; i < 3; i++) {
        assert(result4[i] == strlen(arr3[i]));
    }
    free(result4);

    char** result5 = array_map(arr3, 3, char*, strcat_alloc, "!");
    for (u64 i = 0; i < 3; i++) {
        char* str = strcat_alloc(arr3[i], "!");
        assert(strcmp(result5[i], str) == 0);
        free(str);
        free(result5[i]);
    }
    free(result5);

    return;
}

void test_array_reduce() {
    u64 arr1[] = { 1, 2, 3, 4, 5 };

    u64 result1 = array_reduce(arr1, 5, u64, sum);
    assert(result1 == 15);

    return;
}
