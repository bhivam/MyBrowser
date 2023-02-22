IDIR=../include
ODIR=obj

CC=gcc
CFLAGS=-I -Wextra -Wall -std=c99 -g -fsanitize=address

_DEPS=utils.h parser.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o utils.o parser.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~