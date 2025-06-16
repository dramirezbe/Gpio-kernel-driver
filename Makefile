# Root Makefile

.PHONY: all build_dir app kernel test clean

# Default target: build everything
all: build_dir app kernel test

# Prepare the build directory once
build_dir:
	@mkdir -p build
	@rm -rf build/*
	@echo "▶ Build directory ready."

# Pull into each subdirectory
app: build_dir
	@echo "▶ Building user‐space app…"
	@$(MAKE) -C app

kernel: build_dir
	@echo "▶ Building kernel module…"
	@$(MAKE) -C Core

test: build_dir
	@echo "▶ Building tests…"
	@$(MAKE) -C test

# Tear down everything
clean:
	@echo "▶ Cleaning all artifacts…"
	@rm -rf build
	@$(MAKE) -C app    clean
	@$(MAKE) -C Core   clean
	@$(MAKE) -C test   clean
	@echo "✔ Clean complete."
