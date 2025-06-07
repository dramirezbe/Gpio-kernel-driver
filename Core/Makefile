# Core/Makefile for Kernel Module

# Specify the object file to build from our source
obj-m += gpio_led_driver.o

# Kernel source directory
# Default to the headers for the currently running kernel
KDIR ?= /lib/modules/$(shell uname -r)/build

# Output directory for the final .ko file
BUILD_DIR = ../build

# Default target: build the kernel module
all:
	@echo "  Building kernel module in $(CURDIR)"
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	@cp *.ko $(BUILD_DIR)/

# Target to clean up all generated files
clean:
	@echo "  Cleaning kernel module in $(CURDIR)"
	@$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f *.ko

.PHONY: all clean