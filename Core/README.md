# Kernel Driver Documentation

# Kernel Module: GPIO LED Driver

This folder contains the source code for a Linux kernel module that implements a character device driver for GPIO LED control.

## Description

The driver registers a character device at `/dev/gpioled`. Writing `"1"` to this device turns the LED on, and writing `"0"` turns it off. Reading from the device returns the current LED state (`'1'` or `'0'`).

## Files

- `gpio_led_driver.c`: Main source code for the character device driver.
- `Makefile`: Compiles the kernel module using `make`.

## Build Instructions

To build the kernel module:

```bash
make
