CC = cc
CFLAGS = -Wall -Wextra -std=c11 -pedantic

heap: main.o heap.o
	$(CC) $(CFLAGS) -o heap main.o heap.o

main.o: main.c heap.h Debjit.h
	$(CC) $(CFLAGS) -c main.c

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c