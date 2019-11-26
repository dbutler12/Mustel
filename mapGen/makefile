IDIR=.
CC = gcc
CFLAGS=-I$(IDIR)
DEPS = mustel.h
OBJ = main.o maphandler.o genIO.o map.o files.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

MapGen: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm main.o maphandler.o genIO.o map.o files.o MapGen
