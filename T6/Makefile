CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

PROG = arv

all: arv

principal.o: principal.c

pilha.o: pilha.c pilha.h

arv.o: arv.c arv.h

memo.o: memo.c memo.h

arv: principal.o memo.o arv.o pilha.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
clean:
	rm -f *.o $(PROG)
