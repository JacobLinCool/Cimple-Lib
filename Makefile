all:
	make test -i

compile_test:
	@ echo "Compiling Tests"
	@ gcc ./tests/string.test.c -lm -o ./tests/string_test
	@ gcc ./tests/timing.test.c -lm -o ./tests/timing_test
	@ gcc ./tests/array.test.c -lm -o ./tests/array_test
	@ gcc ./tests/format.test.c -lm -o ./tests/format_test
	@ gcc ./tests/debug.test.c -lm -o ./tests/debug_test
	@ echo "Tests Compiled"

test: compile_test
	@ ./tests/string_test
	@ ./tests/timing_test
	@ ./tests/array_test
	@ ./tests/format_test
	@ ./tests/debug_test
	@ echo "All Tests Finished"
