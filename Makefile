cc = gcc
src_dir = src

test_files = $(wildcard $(src_dir)/*.test.c)

all: test

test: $(test_files)
	@echo "Tests Passed"

$(test_files): force
	@echo "Running test: $(basename $@)"
	@$(cc) -o $(basename $@) -fsanitize=address -D DEBUG $@
	@./$(basename $@)

clean:
	@rm -f $(test_files)
	@echo "Cleaned"

.PHONY: all clean test force
