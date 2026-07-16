CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -Iinclude
BUILD_DIR := build
SRC_DIR := src

CLIENT_SRC := $(SRC_DIR)/client.cpp
SERVER_SRC := $(SRC_DIR)/server.cpp
CLIENT_BIN := $(BUILD_DIR)/client
SERVER_BIN := $(BUILD_DIR)/server

.PHONY: all clean

all: $(CLIENT_BIN) $(SERVER_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(CLIENT_BIN): $(CLIENT_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(SERVER_BIN): $(SERVER_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN)
