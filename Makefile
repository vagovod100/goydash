CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

BUILD_DIR = build
BINARY = goydash
TARGET = $(BUILD_DIR)/$(BINARY)

PREFIX ?= /usr
DATADIR = $(PREFIX)/share/$(BINARY)

SRC = \
	main.c \
	src/parser.c \
	src/executor.c \
	src/utils.c \
	src/builtins.c


CFLAGS += -DGOYDASH_DATADIR=\"$(DATADIR)\"

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

install: $(TARGET)
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	mkdir -p "$(DESTDIR)$(DATADIR)"
	install -m755 "$(TARGET)" "$(DESTDIR)$(PREFIX)/bin/$(BINARY)"
	install -m644 "help.txt" "$(DESTDIR)$(DATADIR)/help.txt"

clean:
	rm -rf $(BUILD_DIR)
