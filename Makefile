# Root Makefile

# Default target: build everything
all: build_dir app kernel test

# Target to set up the build directory
# Creates the directory if it doesn't exist, then clears its contents.
build_dir:
	@mkdir -p build
	@rm -rf build/*
	@echo "Build directory ready."

# Target to build only the user-space application
app: build_dir
	@echo "Building application..."
	@$(MAKE) -C app

# Target to build only the kernel module
kernel: build_dir
	@echo "Building kernel module..."
	@$(MAKE) -C Core

# Target to build the test components
test: build_dir
	@echo "Building tests..."
	@$(MAKE) -C test

# Target to clean the entire project
clean:
	@echo "Cleaning project..."
	@rm -rf build
	@$(MAKE) -C app clean
	@$(MAKE) -C Core clean
	@$(MAKE) -C test clean
	@echo "Project cleaned."

# Phony targets are not files
.PHONY: all build_dir app kernel test clean