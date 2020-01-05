all: server.o
	gcc -o program server.o

server.o: server.c
	gcc -c server.c

run:
		./program

clean:
	rm *.o
	rm *~
