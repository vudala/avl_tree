# GRR20195689 Eduardo Vudala Senoski

# Compiler options
CC = gcc
CFLAGS = -Wall -g
LIBS = -lm

# Compiler I/O
OBJECTS = main.o avl.o
OUTPUT = myavl

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

avl.o: avl.c
	$(CC) $(CFLAGS) -c avl.c

clean:
	rm -rf $(OBJECTS)

purge: clean
	rm -rf $(OUTPUT)