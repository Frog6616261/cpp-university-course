MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRC_DIR := $(MAKEFILE_DIR)../src
BUILD_DIR := $(MAKEFILE_DIR)../build

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

PROGRAMS := sequence threads process

TARGET_SEQUENCE := $(BUILD_DIR)/sequence
TARGET_THREADS := $(BUILD_DIR)/threads
TARGET_PROCESS := $(BUILD_DIR)/process

.PHONY: all build_sequence build_threads build_process \
        run_sequence run_threads run_process \
        clean

all: build_sequence build_threads build_process

$(BUILD_DIR):
	@echo "Create build directory"
	@mkdir -p $(BUILD_DIR)

build_sequence: $(TARGET_SEQUENCE)

build_threads: $(TARGET_THREADS)

build_process: $(TARGET_PROCESS)

$(TARGET_SEQUENCE): $(SRC_DIR)/sequence/main.cpp | $(BUILD_DIR)
	@echo "Start C++ compilation: sequence"
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Compilation complete: $(TARGET_SEQUENCE)"

$(TARGET_THREADS): $(SRC_DIR)/threads/main.cpp | $(BUILD_DIR)
	@echo "Start C++ compilation: threads"
	@$(CXX) $(CXXFLAGS) -pthread $< -o $@
	@echo "Compilation complete: $(TARGET_THREADS)"

$(TARGET_PROCESS): $(SRC_DIR)/process/main.cpp | $(BUILD_DIR)
	@echo "Start C++ compilation: process"
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Compilation complete: $(TARGET_PROCESS)"

run_sequence: build_sequence
	@$(TARGET_SEQUENCE) $(ARGS)

run_threads: build_threads
	@$(TARGET_THREADS) $(ARGS)

run_process: build_process
	@$(TARGET_PROCESS) $(ARGS)

clean:
	@echo "Cleaning build directory"
	@rm -rf $(BUILD_DIR)