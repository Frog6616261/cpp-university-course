MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRC_DIR := $(MAKEFILE_DIR)../src
BUILD_DIR := $(MAKEFILE_DIR)../build

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
PYTHON := python3

SRC_CPP := $(SRC_DIR)/main.cpp
SRC_PY := $(SRC_DIR)/main.py

TARGET_CPP := $(BUILD_DIR)/main
TARGET_PY := $(BUILD_DIR)/main.pyc

.PHONY: build_cpp build_py run_cpp run_py clean

build_cpp: $(TARGET_CPP)

build_py: $(TARGET_PY)

$(BUILD_DIR):
	@echo "Create build directory"
	@mkdir -p $(BUILD_DIR)

$(TARGET_CPP): $(SRC_CPP) | $(BUILD_DIR)
	@echo "Start C++ compilation"
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "C++ compilation complete"

$(TARGET_PY): $(SRC_PY) | $(BUILD_DIR)
	@echo "Start Python compilation"
	@$(PYTHON) -c "import py_compile; py_compile.compile(r'$(SRC_PY)', cfile=r'$(TARGET_PY)', doraise=True)"
	@echo "Python compilation complete"

run_cpp: build_cpp
	@$(TARGET_CPP) $(ARGS)

run_py:
	@$(PYTHON) $(SRC_PY)

clean:
	@echo "Cleaning build directory"
	@rm -rf $(BUILD_DIR)