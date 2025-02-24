# Compiler
CC = gcc

# Flags
CFLAGS = -Iinclude -Llib
LDFLAGS = -lSDL3

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

# DLL to copy
DLL = $(BIN_DIR)/SDL3.dll

# Default target
all: $(TARGET)
	cp $(DLL) $(BUILD_DIR)/
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