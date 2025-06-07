# test/Makefile

CC = gcc
CFLAGS = -Wall -Wextra

# Find all .c files in this directory
SOURCES = $(wildcard *.c)
# Create a list of executables based on the source files (e.g., my_test.c -> my_test)
TARGETS = $(patsubst %.c,%,$(SOURCES))

BUILD_DIR = ../build

# Default target: build all test executables
all: $(addprefix $(BUILD_DIR)/, $(TARGETS))

# Generic rule to build any test executable
$(BUILD_DIR)/%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up intermediate files
clean:
	@rm -f *.o

.PHONY: all clean