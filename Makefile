CC = gcc
FLAGS = -fsanitize=address -Wall -Wextra -lm -D DEBUG

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.h)
TEST_SRCS = $(wildcard $(SRC_DIR)/*.test.c)
TEST_OUTS = $(patsubst %.test.c,%.out,$(TEST_SRCS))

VERSION := $(shell git describe --tags --abbrev=0)
DATE := $(shell date +%Y-%m-%d)

all: clean test

test: $(TEST_OUTS)
	@echo "All Tests Passed"

$(TEST_OUTS): $(patsubst %.out,%.test.c,$@)
	@echo "Running test: $(patsubst src/%.out,%,$@)"
	@$(CC) $(FLAGS) -o $@ $(patsubst %.out,%.test.c,$@)
	@./$@

clean:
	rm -f $(TEST_OUTS) *.zip
	@echo "Cleaned"

release:
	sed -i "s/@version.*/@version $(VERSION)/g" $(SRCS)
	sed -i "s/@date.*/@date $(DATE)/g" $(SRCS)
	zip -r cimple-$(VERSION).zip src/*.h
	@echo "Created cimple-$(VERSION).zip"

unrelease:
	sed -i "s/@version.*/@version/g" $(SRCS)
	sed -i "s/@date.*/@date/g" $(SRCS)
	rm -f cimple-$(VERSION).zip

.PHONY: all test clean
