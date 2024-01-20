CC = gcc
CFLAGS = -Wall
LIBS = -lncurses

SRC = main.c  # Add more source files if needed
OBJ = $(SRC:.c=.o)

all: piano_tiles

piano_tiles: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) piano_tiles

.PHONY: all clean
