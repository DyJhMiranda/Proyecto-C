CC  := gcc
TARGETS := p1 p2

p1: proyecto1.o
	$(CC) -g proyecto1.o -lm -o exe 

p2: proyecto2.o
	$(CC) -g proyecto2.o -lm -o exe

clean:
	rm exe *.o
