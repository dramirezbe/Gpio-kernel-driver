# Documentation for user app led control


---

### 📁 `app/README.md`

```markdown
# User Space Application: LED Control Interface

This folder contains a C program that interacts with the `/dev/gpioled` device to control an external LED via command line.

## Description

This application allows users to:
- Turn the LED on or off
- Query the current LED state

## Files

- `led_control_app.c`: Source code of the command-line application.
- `Makefile`: Compiles the application.

## Build Instructions

```bash
make
