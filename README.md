# Made By:
- Leandro Zapata Marin
- David Ramírez Betancourth

# Gpio-kernel-driver
This Program consist in use C libraries adecuated to produce a kernel driver (maximum authority driver), this program controls a gpio status, with user control. A complete Linux character device driver and user-space application for controlling an LED connected to a GPIO pin.

## 📚 Project Description

This project demonstrates the implementation of a Linux kernel module that registers a character device at `/dev/gpioled`. A corresponding user-space application allows users to turn an external LED on or off and check its status.

## 🧠 Learning Objectives

- Understand how to build and register Linux character device drivers.
- Interface kernel modules with user-space applications.
- Control GPIOs from both kernel and user space.
- Apply sound software engineering practices: modular code, testing, documentation, and version control.

## 🗂️ Repository Structure

```plaintext
.
├── core/       # Kernel module source code (driver)
├── app/        # User-space application (LED control interface)
├── test/       # Test programs for both the driver and the app
