IDIR=.
CC = gcc
CFLAGS=-I$(IDIR) -lncurses
DEPS = mustel.h
OBJ = main.o testFun.o files.o map.o loaders.o spawner.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

Mustel: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o files.o map.o loaders.o spawner.o Mustel
