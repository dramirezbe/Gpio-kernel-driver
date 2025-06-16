# app/Makefile

.PHONY: all clean

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99
SRC     := led_control_app.c
TARGET  := led_control_app
BUILD_DIR := $(abspath ../build)

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC)
	@echo "    ↪ Compiling $< → $@"
	$(CC) $(CFLAGS) -o $@ $<

clean:
	@echo "    ↪ Cleaning user‐space app in $(CURDIR)"
	@rm -f $(BUILD_DIR)/$(TARGET)
