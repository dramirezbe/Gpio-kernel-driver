# Test Documentation 📁 `test/README.md`

```markdown
# Test Suite: GPIO LED Driver and App

This folder contains test programs designed to verify the correctness and reliability of both the kernel driver and the user-space application.

## Description

- `gpio_led_driver_test`: Interacts directly with `/dev/gpioled` to test write/read functionality and error handling.
- `led_control_app_test`: Automates common command-line calls to `led_control_app` to validate its behavior.

## Files

- `gpio_led_driver_test.c`: Tests direct access to the character device.
- `led_control_app_test.c`: Tests the user interface application.
- `Makefile`: Builds both test programs.

## Build Instructions

```bash
make
