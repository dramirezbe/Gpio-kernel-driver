# Core/Makefile

obj-m += gpio_led_driver.o

# point at your kernel headers
KDIR ?= /lib/modules/$(shell uname -r)/build

# where to place the final .ko
BUILD_DIR := $(abspath ../build)

.PHONY: all clean

all:
	@echo "    ↪ Building kernel module in $(CURDIR)"
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	@cp -v *.ko $(BUILD_DIR)/

clean:
	@echo "    ↪ Cleaning kernel module in $(CURDIR)"
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f *.ko
