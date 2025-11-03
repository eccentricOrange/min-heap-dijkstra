# --- Minimal Makefile for DSA C 101 Assignment ---

# Configuration Variables
CC = gcc
CFLAGS = -I$(INCDIR) -Wall -Wextra

SRCDIR = src
INCDIR = inc
BINDIR = bin

# Automatic File Discovery (for 'build' and individual compilation)
C_FILES = $(wildcard $(SRCDIR)/*.c)
TARGETS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%, $(C_FILES))

# --- Manually Maintained Autocomplete Targets ---
# Add the base names of your .c files (without extension) and other common targets here.
# Example: If you have src/my_program.c, add 'my_program' to this list.
# You will need to manually update this list as you add new .c files or targets.
AUTOCOMPLETE_SUGGESTIONS = all build clean dijkstra

# Phony Targets
.PHONY: all build clean $(AUTOCOMPLETE_SUGGESTIONS)

# Main Build Targets
all: build

build: $(TARGETS)
	@echo "Build complete. Executables are in the '$(BINDIR)' directory."

# Rule for compiling C files into the bin directory
$(BINDIR)/%: $(SRCDIR)/%.c | $(BINDIR)
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $< -o $@

# Rule to create the bin directory
$(BINDIR):
	@mkdir -p $(BINDIR)

# --- Rule to link command-line target names to their compiled executables ---
# This ensures that 'make check_parenthesis' correctly triggers the compilation
# of 'bin/check_parenthesis' if needed.
$(patsubst $(SRCDIR)/%.c, %, $(C_FILES)): %: $(BINDIR)/%
	@echo "Target '$@' requested. Ensuring $(BINDIR)/$@ is up-to-date."

# Clean Target
clean:
	@echo "Cleaning up compiled executables..."
	@rm -f $(BINDIR)/*
	@echo "Clean complete."

# --- Available Targets (for reference) ---
# - 'make' or 'make all': Compiles all .c files into executables in the 'bin' folder.
# - 'make build': Same as 'make all'.
# - 'make <filename_without_extension>': Compiles a specific .c file.
#   Example: 'make check_parenthesis' will compile src/check_parenthesis.c into bin/check_parenthesis.
# - 'make clean': Removes all compiled executables from the 'bin' folder.
