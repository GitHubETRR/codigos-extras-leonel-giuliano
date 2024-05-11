CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=

# Source files
SOURCES=main.c
HEADERS=mallist.h

# Dynamic libraries (.dll files)
DLLS=$(wildcard *.dll)

# Object files
OBJECTS=$(addprefix $(OUTPUT_DIR)/, $(SOURCES:.c=.o))

# Output directory
OUTPUT_DIR=output

# Executable name
EXECUTABLE=$(OUTPUT_DIR)/main.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(DLLS)

$(OUTPUT_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OUTPUT_DIR)/*.o