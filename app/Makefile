# app/Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Source file and output executable
SRC = led_control_app.c
TARGET = led_control_app
BUILD_DIR = ../build

# Default target: build the application
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

# Clean up intermediate files
clean:
	@rm -f *.o

.PHONY: all clean