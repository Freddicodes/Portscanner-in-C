CC = gcc
CFLAGS = -pedantic -Wall -Wextra

scanner:  scanner.o
	$(CC) scanner.o main.c -o scanner $(CFLAGS)
scanner.o: scanner.h scanner.c
	$(CC) -c scanner.h scanner.c $(CFLAGS)

clean:
	rm *.o
	rm *.h.gch