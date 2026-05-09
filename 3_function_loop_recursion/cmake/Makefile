MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRC_DIR := $(MAKEFILE_DIR)../src
BUILD_DIR := $(MAKEFILE_DIR)../build

CXX := g++
CXXFLAGS := -fsanitize=address -std=c++17 -Wall -Wextra -Wpedantic -g 

SRC_CALC := $(SRC_DIR)/calc/main.cpp
SRC_TOWERS := $(SRC_DIR)/towers/main.cpp

TARGET_CALC := $(BUILD_DIR)/main_calc
TARGET_TOWERS := $(BUILD_DIR)/main_towers

.PHONY: build_cpp run_calc run_towers clean

build_cpp: $(TARGET_CALC) $(TARGET_TOWERS)

$(BUILD_DIR):
	@echo "Create build directory"
	@mkdir -p $(BUILD_DIR)

$(TARGET_CALC): $(SRC_CALC) | $(BUILD_DIR)
	@echo "Start calc compilation"
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Calc compilation complete"

$(TARGET_TOWERS): $(SRC_TOWERS) | $(BUILD_DIR)
	@echo "Start towers compilation"
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Towers compilation complete"

run_calc: $(TARGET_CALC)
	@$(TARGET_CALC) $(ARGS)

run_towers: $(TARGET_TOWERS)
	@$(TARGET_TOWERS) $(ARGS)

clean:
	@echo "Cleaning build directory"
	@rm -rf $(BUILD_DIR)