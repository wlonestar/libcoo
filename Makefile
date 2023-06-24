CC = gcc
CFLAGS = -std=c99 -Wall -g -Iinclude

TEST_DIR = test
INCLUDE_DIR = include

TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
EXECUTABLES = $(patsubst $(TEST_DIR)/%.c, %, $(TEST_FILES))

$(TEST_DIR)/%.c: $(INCLUDE_DIR)/%.h 
	$(CC) $(CFLAGS) -o $(EXECUTABLES) $^

%: $(TEST_DIR)/%.c 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXECUTABLES)

.PHONY: message 
message:
	@echo "CC = $(CC)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "TEST_DIR = $(TEST_DIR)" 
	@echo "INCLUDE_DIR = $(INCLUDE_DIR)"
	@echo "TEST_FILES = $(TEST_FILES)"
	@echo "EXECUTABLES = $(EXECUTABLES)"

