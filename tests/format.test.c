#include "../lib/base.h"
#include "../lib/format.h"

i32 main() {
    printf("-- Format need some visual checks. --\n");

    printf(
        "%s | %s | %s | %s | %s | %s\n\n",
        tint("CLR RED", CLR_RED),
        tint("CLR GREEN", CLR_GREEN),
        tint("CLR YELLOW", CLR_YELLOW),
        tint("CLR BLUE", CLR_BLUE),
        tint("CLR MAGENTA", CLR_MAGENTA),
        tint("CLR CYAN", CLR_CYAN)
    );

    i8 arr1[5] = { -1, 2, -3, 4, -5 };
    char arr2[] = "Hello, World!";
    string arr3[] = { "Hello", "World" };
    f128 arr4[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
    u32 arr5[] = { 16, 64, 256, 1024, 4096 };
    string arr6[] = { "Hello", "World", "12345" };

    string arr_str1 = format_array(i8, arr1, -1, 10);
    printf("%s\n\n", arr_str1);

    string arr_str2 = format_array(char, arr2, 0, strlen(arr2) - 1);
    printf("%s\n\n", arr_str2);

    string arr_str3 = format_array(str, arr3, 0, 1);
    printf("%s\n\n", arr_str3);

    string arr_str3_ptr = format_array(ptr, arr3, 0, 1);
    printf("%s\n\n", arr_str3_ptr);

    string arr_str4 = format_array(f128, arr4, 0, 4);
    printf("%s\n\n", arr_str4);

    string arr_str5 = format_array(x32, arr5, 0, 4);
    printf("%s\n\n", arr_str5);

    string arr_str7 = format_array(ptr, arr6, 0, 2);
    printf("%s\n\n", arr_str7);

    printf("-- Format need some visual checks. --\n");

    return 0;
}
