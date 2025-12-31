CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

BUILD_DIR := build
APP       := $(BUILD_DIR)/app

SOURCES := $(shell find src -name "*.cpp")

all: $(APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(APP): $(BUILD_DIR) $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(APP)

run: all
	./$(APP)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
