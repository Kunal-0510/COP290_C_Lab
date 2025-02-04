CC = gcc
CFLAGS = -Wall -g

OBJECTS = main.o Node.o linkedlist.o Queue.o Sheet.o hash.o validity.o functions.o parsing.o display.o

all: myprogram

myprogram: $(OBJECTS)
	$(CC) $(CFLAGS) -o myprogram $(OBJECTS)

Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c Node.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) -c Queue.c

validity.o: validity.c validity.h
	$(CC) $(CFLAGS) -c validity.c

Sheet.o: Sheet.c Sheet.h Node.h
	$(CC) $(CFLAGS) -c Sheet.c

hash.o: hash.c hash.h Sheet.h Node.h
	$(CC) $(CFLAGS) -c hash.c

functions.o: functions.c Functions.h Node.h Sheet.h hash.h linkedlist.h Queue.h
	$(CC) $(CFLAGS) -c functions.c

parsing.o: parsing.c parsing.h hash.h validity.h Node.h Sheet.h Functions.h
	$(CC) $(CFLAGS) -c parsing.c

display.o: display.c display.h Node.h Sheet.h
	$(CC) $(CFLAGS) -c display.c

main.o: main.c Functions.h Node.h Sheet.h display.h hash.h linkedlist.h parsing.h Queue.h validity.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o myprogram

.PHONY: all clean