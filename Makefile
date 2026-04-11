CC = gcc

# List of directories containing source files.
SRC_DIRS := . cli SortingAlgorithms SearchingAlgorithms LinkedList Stack

# Directory to store the build files (object files and dependency files).
BUILD_DIR := build

# Path to the final executable.
EXE := $(BUILD_DIR)/dataStructuresDemo

# Generate a list of all source files in the specified directories and create corresponding object file names.
SRCS := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

# -I includes the directories for header files. -I must be prefixed to each directory with header files.
CFLAGS   := -Wall -g -MMD -MP $(addprefix -I,$(SRC_DIRS))
LDFLAGS  := -Llib
LDLIBS   := -lm

# These targets don't correspond to actual files/folders, so we mark them as phony to avoid conflicts with files/folders of the same name
.PHONY: all clean

all: $(EXE)

# Build the executable by linking the object files.
$(EXE): $(OBJS) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	@printf "\nExecutable located at %s\n" "$@"

# Compile source files into object files.
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist.
$(BUILD_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BUILD_DIR)

