# Compiler
CC = gcc -Wall -g

# Flags
CFLAGS = -Iinclude

ifeq ($(OS),Windows_NT)
	CFLAGS += -Llib/windows
else
	UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
		CFLAGS += -Llib/linux
	else ifeq ($(UNAME_S),Darwin)
		CFLAGS += -Llib/macos
	endif
endif
LDFLAGS = -lm -lSDL3 -lSDL3_ttf -lSDL3_mixer -lcJSON

# Directories
BUILD_DIR = build
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Object directories
OBJ_DIRS = $(sort $(dir $(OBJ)))

# Target executable
TARGET = $(BUILD_DIR)/main.exe

# DLL to copy (windows only)
DLL = $(wildcard $(BIN_DIR)/*.dll)

# Default target
all: $(TARGET)
ifeq ($(OS),Windows_NT)
	cp $(DLL) $(BUILD_DIR)/
endif
	./$(TARGET)

create-build-dirs:
	@mkdir -p $(OBJ_DIRS)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | create-build-dirs
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Link object files to executable
$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean create-build-dirs