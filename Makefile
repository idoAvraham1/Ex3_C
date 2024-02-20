CC= gcc
CFLAGS= -Wall -g

all: StrList

main.o: main.c StrList.h
	$(CC) $(CFLAGS) -c $< -o $@

StrList.o: StrList.c StrList.h 
	$(CC) $(CFLAGS) -c StrList.c

StrList: main.o StrList.o
	$(CC) $(CFLAGS) StrList.o main.o -o StrList

clean: 
	rm -f *.o StrList