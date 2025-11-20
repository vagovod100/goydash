CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
TARGET = goydash
SRC = \
	main.c \
	src/parser.c \
	src/executor.c \
	src/utils.c \
	src/builtins.c
BUILD_DIR = build
TARGET = $(BUILD_DIR)/goydash

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -rf $(BUILD_DIR)
