ODIR=bin/obj
BIN=bin

CC=gcc
CFLAGS=-I -Wextra -Wall -std=c99 -g -fsanitize=address

DEPS=src/utils.h src/parser.h

_OBJ=main.o utils.o parser.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN)/main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

