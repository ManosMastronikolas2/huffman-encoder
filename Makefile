CC = gcc
CFLAGS = -Wall -Wextra 
TARGET = bin/huffman

SRCS = main.c huffman.c heap.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf bin

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
