CC=gcc
CFLAGS=-Iinclude -Wall -Wextra
SRC=src
BUILD=build
TARGET=quiz

SOURCES=$(wildcard $(SRC)/*.c)
OBJECTS=$(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(SOURCES))

all: $(BUILD)/$(TARGET)

$(BUILD)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $^ -lncurses -o $@

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

run: $(BUILD)/$(TARGET)
	./$(BUILD)/$(TARGET)

.PHONY: all clean run