CXX := g++
CPPFLAGS := -Iinclude
COMMON_CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic
DEBUG_CXXFLAGS := -g -O0
RELEASE_CXXFLAGS := -O2 -DNDEBUG
SRC_DIR := src

DEBUG_BUILD_DIR := build/debug
DEBUG_OBJ_DIR := $(DEBUG_BUILD_DIR)/obj
RELEASE_BUILD_DIR := build/release
RELEASE_OBJ_DIR := $(RELEASE_BUILD_DIR)/obj

CLIENT_SRCS := \
	$(SRC_DIR)/client/main.cpp \
	$(SRC_DIR)/client/client.cpp \
	$(SRC_DIR)/common/socket.cpp

SERVER_SRCS := \
	$(SRC_DIR)/server/main.cpp \
	$(SRC_DIR)/server/server.cpp \
	$(SRC_DIR)/common/socket.cpp

DEBUG_CLIENT_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(DEBUG_OBJ_DIR)/%.o,$(CLIENT_SRCS))
DEBUG_SERVER_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(DEBUG_OBJ_DIR)/%.o,$(SERVER_SRCS))
RELEASE_CLIENT_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(RELEASE_OBJ_DIR)/%.o,$(CLIENT_SRCS))
RELEASE_SERVER_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(RELEASE_OBJ_DIR)/%.o,$(SERVER_SRCS))

DEBUG_CLIENT_BIN := $(DEBUG_BUILD_DIR)/client
DEBUG_SERVER_BIN := $(DEBUG_BUILD_DIR)/server
RELEASE_CLIENT_BIN := $(RELEASE_BUILD_DIR)/client
RELEASE_SERVER_BIN := $(RELEASE_BUILD_DIR)/server

.PHONY: all debug release clean

all: release

debug: $(DEBUG_CLIENT_BIN) $(DEBUG_SERVER_BIN)

release: $(RELEASE_CLIENT_BIN) $(RELEASE_SERVER_BIN)

$(DEBUG_CLIENT_BIN): $(DEBUG_CLIENT_OBJS) | $(DEBUG_BUILD_DIR)
	$(CXX) $(COMMON_CXXFLAGS) $(DEBUG_CXXFLAGS) $^ -o $@

$(DEBUG_SERVER_BIN): $(DEBUG_SERVER_OBJS) | $(DEBUG_BUILD_DIR)
	$(CXX) $(COMMON_CXXFLAGS) $(DEBUG_CXXFLAGS) $^ -o $@

$(RELEASE_CLIENT_BIN): $(RELEASE_CLIENT_OBJS) | $(RELEASE_BUILD_DIR)
	$(CXX) $(COMMON_CXXFLAGS) $(RELEASE_CXXFLAGS) $^ -o $@

$(RELEASE_SERVER_BIN): $(RELEASE_SERVER_OBJS) | $(RELEASE_BUILD_DIR)
	$(CXX) $(COMMON_CXXFLAGS) $(RELEASE_CXXFLAGS) $^ -o $@

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(DEBUG_OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(COMMON_CXXFLAGS) $(DEBUG_CXXFLAGS) -c $< -o $@

$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(RELEASE_OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(COMMON_CXXFLAGS) $(RELEASE_CXXFLAGS) -c $< -o $@

$(DEBUG_BUILD_DIR):
	mkdir -p $(DEBUG_BUILD_DIR)

$(RELEASE_BUILD_DIR):
	mkdir -p $(RELEASE_BUILD_DIR)

$(DEBUG_OBJ_DIR):
	mkdir -p $(DEBUG_OBJ_DIR)

$(RELEASE_OBJ_DIR):
	mkdir -p $(RELEASE_OBJ_DIR)

clean:
	rm -rf build
