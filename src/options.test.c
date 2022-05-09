#include "options.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int32_t argc1 = 1;
    char*   argv1[] = {"./program"};

    ParsedOptions* options = Options.parse(argc1, argv1);
    assert(options->option_count == 0);
    assert(options->wild_count == 0);
    Options.free(options);

    int32_t argc2 = 3;
    char*   argv2[] = {"./program", "--test", "-f"};

    options = Options.parse(argc2, argv2);
    assert(options->option_count == 2);
    assert(options->wild_count == 0);
    assert(Options.has(options, "test") && Options.get(options, "test") == NULL);
    assert(Options.has(options, "f") && Options.get(options, "f") == NULL);
    Options.free(options);

    int32_t argc3 = 5;
    char*   argv3[] = {"./program", "--test", "value 123", "-f", "value 456"};

    options = Options.parse(argc3, argv3);
    assert(options->option_count == 2);
    assert(options->wild_count == 0);
    assert(Options.has(options, "test") && strcmp(Options.get(options, "test"), "value 123") == 0);
    assert(Options.has(options, "f") && strcmp(Options.get(options, "f"), "value 456") == 0);
    Options.free(options);

    int32_t argc4 = 5;
    char*   argv4[] = {"./program", "--key", "value 123", "file 1.txt", "file 2.txt"};
    options = Options.parse(argc4, argv4);
    assert(options->option_count == 1);
    assert(options->wild_count == 2);
    assert(Options.has(options, "key") && strcmp(Options.get(options, "key"), "value 123") == 0);
    assert(options->wilds[0] && strcmp(options->wilds[0], "file 1.txt") == 0);
    assert(options->wilds[1] && strcmp(options->wilds[1], "file 2.txt") == 0);
    Options.free(options);

    int32_t argc5 = 5;
    char*   argv5[] = {"./program", "file 1.txt", "file 2.txt", "--key", "value 123"};
    options = Options.parse(argc5, argv5);
    assert(options->option_count == 1);
    assert(options->wild_count == 2);
    assert(Options.has(options, "key") && strcmp(Options.get(options, "key"), "value 123") == 0);
    assert(options->wilds[0] && strcmp(options->wilds[0], "file 1.txt") == 0);
    assert(options->wilds[1] && strcmp(options->wilds[1], "file 2.txt") == 0);
    Options.free(options);

    int32_t argc6 = 7;
    char*   argv6[] = {"./program", "file 1.txt", "--key",     "value 123",
                     "--key2",    "value 456",  "file 2.txt"};
    options = Options.parse(argc6, argv6);
    assert(options->option_count == 2);
    assert(options->wild_count == 2);
    assert(Options.has(options, "key") && strcmp(Options.get(options, "key"), "value 123") == 0);
    assert(Options.has(options, "key2") && strcmp(Options.get(options, "key2"), "value 456") == 0);
    assert(options->wilds[0] && strcmp(options->wilds[0], "file 1.txt") == 0);
    assert(options->wilds[1] && strcmp(options->wilds[1], "file 2.txt") == 0);
    Options.free(options);

    int32_t argc7 = 5;
    char*   argv7[] = {"./program", "--key", "value", "--bool", "file.txt"};
    options = Options.parse(argc7, argv7);
    assert(options->option_count == 2);
    assert(options->wild_count == 0);
    Options.key_only(options, "bool");
    assert(options->option_count == 2);
    assert(options->wild_count == 1);
    assert(Options.has(options, "key") && strcmp(Options.get(options, "key"), "value") == 0);
    assert(Options.has(options, "bool") && Options.get(options, "bool") == NULL);
    assert(options->wilds[0] && strcmp(options->wilds[0], "file.txt") == 0);
    Options.free(options);

    return EXIT_SUCCESS;
}
