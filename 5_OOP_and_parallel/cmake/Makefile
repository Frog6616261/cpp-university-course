CXX := g++

CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g3 -O0 -I$(INCLUDE_DIR) -MMD -MP

SRC_DIR := ../src
BUILD_DIR := ../build
INCLUDE_DIR := ../include

TARGET := $(BUILD_DIR)/main

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all run clean rebuild

-include $(DEPS)