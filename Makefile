CC = gcc
CFLAGS = -std=c11 -Wall -g -Iinclude -fsanitize=address

TEST_DIR = test
EXAMPLES_DIR = examples
BUILD_DIR = build

.DEFAULT_GOAL := build

config:
	mkdir -p build

test: config
	for f in $(TEST_DIR)/*.c; do \
		$(CC) $(CFLAGS) -o $(BUILD_DIR)/`basename $$f .c` $$f; \
	done

example: config
	for f in $(EXAMPLES_DIR)/*.c; do \
		$(CC) $(CFLAGS) -o $(BUILD_DIR)/`basename $$f .c` $$f; \
	done

build: test example

run:
	./$(BUILD_DIR)/$(NAME)

gdb:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(NAME) ./test/$(NAME).c
	gdb $(BUILD_DIR)/$(NAME)

gdbgui:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(NAME) ./test/$(NAME).c
	gdbgui $(BUILD_DIR)/$(NAME)

clean:
	rm -f build/*

.PHONY: message clean gdb
