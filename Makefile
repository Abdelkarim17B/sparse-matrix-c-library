CC = gcc
CFLAGS = -Wall -Wextra -std=c99
DEBUG_FLAGS = -g -DDEBUG
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj

# Source files
SOURCES = $(SRC_DIR)/sparse_matrix.c $(SRC_DIR)/matrix_operations.c $(SRC_DIR)/logical_operations.c
MAIN_SRC = $(SRC_DIR)/main.c
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executables
TARGET = sparse_matrix
TEST_TARGETS = $(TEST_SOURCES:$(TEST_DIR)/%.c=%)

.PHONY: all clean test debug help

all: $(TARGET)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build main program
$(TARGET): $(OBJECTS) $(MAIN_OBJ) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build with debug information
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Build and run tests
test: $(TEST_TARGETS)
	@echo "Running tests..."
	@for test in $(TEST_TARGETS); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo "All tests passed!"

# Build individual test executables
test_basic: $(OBJECTS) $(OBJ_DIR)/test_basic.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

test_operations: $(OBJECTS) $(OBJ_DIR)/test_operations.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

test_logical: $(OBJECTS) $(OBJ_DIR)/test_logical.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Clean build files
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET) $(TEST_TARGETS)

# Display help
help:
	@echo "Available targets:"
	@echo "  all      - Build the main program (default)"
	@echo "  debug    - Build with debug information"
	@echo "  test     - Build and run all tests"
	@echo "  clean    - Remove all build files"
	@echo "  help     - Display this help message"

# Dependencies
$(OBJ_DIR)/sparse_matrix.o: $(SRC_DIR)/sparse_matrix.h
$(OBJ_DIR)/matrix_operations.o: $(SRC_DIR)/matrix_operations.h $(SRC_DIR)/sparse_matrix.h
$(OBJ_DIR)/logical_operations.o: $(SRC_DIR)/logical_operations.h $(SRC_DIR)/sparse_matrix.h
$(OBJ_DIR)/main.o: $(SRC_DIR)/sparse_matrix.h $(SRC_DIR)/matrix_operations.h $(SRC_DIR)/logical_operations.h